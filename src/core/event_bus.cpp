//
// Created by Pablo Quiroga on 09/10/2026.
//
#include "event_bus.h"
#include <iostream>

void EventBus::subscribe(const EventType& type, Callback callback) {
    // Agregamos el callback al vector asociado al tipo de evento
    subscribers[type].push_back(callback);
}

void EventBus::publish(const EventType& type, const EventPayload& payload) {
    // Buscamos si existen suscriptores para este evento
    auto it = subscribers.find(type);
    if (it != subscribers.end()) {
        // Ejecutamos cada callback almacenado en la lista
        for (const auto& callback : it->second) {
            callback(payload);
        }
    }
}

void EventBus::unsubscribe(const EventType& type, Callback callback) {
    // Nota: Comparar std::function es complejo en C++.
    // En una versión avanzada usaríamos IDs de suscripción.
    // Por ahora, dejaremos esta función para el Sprint de Refinamiento.
}