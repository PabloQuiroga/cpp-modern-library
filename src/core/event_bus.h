//
// Created by Pablo Quiroga on 09/10/2026.
//

#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <any>
#include <memory>
#include <queue>            // Para la cola de eventos
#include <mutex>            // Para proteger la cola
#include <condition_variable> // Para avisar al worker
#include <thread>           // Para el hilo de ejecución
#include <atomic>           // Para el control de apagado

using EventType = std::string;
using EventPayload = std::any;
using Callback = std::function<void(const EventPayload&)>;

// Definimos la estructura de un Evento pendiente
struct PendingEvent {
    EventType type;
    EventPayload payload;
};

class EventBus {
public:
    EventBus();
    ~EventBus();

    // API Pública
    void subscribe(const EventType& type, Callback callback);
    void publish(const EventType& type, const EventPayload& payload);
    void unsubscribe(const EventType& type, Callback callback);

private:
    // Gestión de suscriptores
    std::unordered_map<EventType, std::vector<Callback>> subscribers;
    std::mutex subscribers_mutex; // Protege el mapa de suscriptores

    // Infraestructura Asíncrona
    std::queue<PendingEvent> event_queue;
    std::mutex queue_mutex;              // Protege la cola
    std::condition_variable condition;   // Sincroniza el worker
    std::thread worker_thread;           // El hilo que procesa los eventos
    std::atomic<bool> stop_worker{false}; // Controla la parada del hilo

    // El bucle infinito que corre en el hilo de fondo
    void worker_loop();
};

#endif