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

// Definimos alias para mayor claridad
using EventType = std::string;
using EventPayload = std::any;
using Callback = std::function<void(const EventPayload&)>;

class EventBus {
public:
    // Evitamos la copia del EventBus para asegurar que haya una única fuente de verdad
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    // Constructor y destructor
    EventBus() = default;
    ~EventBus() = default;

    // API Pública
    void subscribe(const EventType& type, Callback callback);
    void publish(const EventType& type, const EventPayload& payload);
    void unsubscribe(const EventType& type, Callback callback);

private:
    // El mapa de suscriptores: Evento -> Lista de funciones a ejecutar
    std::unordered_map<EventType, std::vector<Callback>> subscribers;
};

#endif