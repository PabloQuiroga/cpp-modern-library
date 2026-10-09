//
// Created by Pablo Quiroga on 08/10/2026.
//
#include <iostream>
#include <string>
#include "core/event_bus.h"

int main() {
    EventBus bus;

    // Definimos un callback para el evento "USER_LOGIN"
    // Usamos una lambda para que sea más conciso
    bus.subscribe("USER_LOGIN", [](const EventPayload& payload) {
        try {
            std::string username = std::any_cast<std::string>(payload);
            std::cout << "Notification: User " << username << " has logged in!" << std::endl;
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error: Invalid payload type for USER_LOGIN" << std::endl;
        }
    });

    // Publicamos el evento
    std::cout << "Publishing USER_LOGIN event..." << std::endl;
    bus.publish("USER_LOGIN", std::string("Pablo"));

    return 0;
}
