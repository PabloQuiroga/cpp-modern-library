//
// Created by Pablo Quiroga on 09/10/2026.
//
#include "event_bus.h"
#include <iostream>

EventBus::EventBus() {
    // Lanzamos el hilo worker al crear el bus
    worker_thread = std::thread(&EventBus::worker_loop, this);
}

EventBus::~EventBus() {
    // 1. Avisamos al worker que debe detenerse
    stop_worker = true;
    // 2. Lo despertamos si estaba durmiendo
    condition.notify_one();
    // 3. Esperamos a que el hilo termine su ejecución actual
    if (worker_thread.joinable()) {
        worker_thread.join();
        }
}

void EventBus::subscribe(const EventType& type, Callback callback) {
    std::lock_guard<std::mutex> lock(subscribers_mutex);

    // Generamos el ID único y creamos la estructura Subscription
    SubscriptionId id = next_id++;
    subscribers[type].push_back({id, callback});
}

void EventBus::publish(const EventType& type, const EventPayload& payload) {
    {
        // Bloqueamos la cola para añadir el evento
        std::lock_guard<std::mutex> lock(queue_mutex);
        event_queue.push({type, payload});
    }
    // Avisamos al hilo worker que hay trabajo pendiente
    condition.notify_one();
}

void EventBus::worker_loop() {
    while (true) {
        PendingEvent event;
        {
            // Bloqueamos y esperamos a que haya eventos o orden de parada
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this] {
                return !event_queue.empty() || stop_worker;
            });

            if (stop_worker && event_queue.empty()) break;

            // Extraemos el primer evento de la cola
            event = event_queue.front();
            event_queue.pop();
        }

        // Ejecutamos los callbacks (fuera del lock de la cola para no bloquear)
        std::lock_guard<std::mutex> lock(subscribers_mutex);
        auto it = subscribers.find(event.type);
        if (it != subscribers.end()) {
            for (const auto& sub : it->second) {
                sub.callback(event.payload); // <--- Accedemos a .callback
            }
        }
    }
}

void EventBus::unsubscribe(const EventType& type, SubscriptionId id) {
    // 1. Bloqueamos la estructura de suscriptores para evitar race conditions
    std::lock_guard<std::mutex> lock(subscribers_mutex);

    // 2. Buscamos si existe la lista de suscriptores para este tipo de evento
    auto it = subscribers.find(type);
    if (it == subscribers.end()) {
        return; // El evento no existe, no hay nada que eliminar
    }

    // 3. Obtenemos la referencia al vector de suscripciones
    auto& list = it->second;

    // 4. Buscamos la suscripción con el ID dado
    for (auto it = list.begin(); it != list.end(); ) {
        if (it->id == id) {
            it = list.erase(it); // erase devuelve el siguiente iterador válido
            break; // Salimos porque el ID es único
        } else {
            ++it; // Solo avanzamos si no borramos nada
        }
    }
}