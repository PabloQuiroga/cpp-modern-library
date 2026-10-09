//
// Created by Pablo Quiroga on 09/10/2026.
//

#include "../src/core/event_bus.h"
#include "test_framework.h"
#include <string>
#include <vector>
#include <thread>
#include <chrono>

// Función auxiliar para esperar al worker
void wait_for_worker() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// TEST 1: Verificar que un suscriptor recibe el evento
bool test_single_subscriber() {
    EventBus bus;
    bool notified = false;
    std::string received_val;

    bus.subscribe("TEST_EVENT", [&](const EventPayload& payload) {
        notified = true;
        received_val = std::any_cast<std::string>(payload);
    });

    bus.publish("TEST_EVENT", std::string("Hello World"));

    wait_for_worker();

    ASSERT_TRUE(notified == true, "Subscriber should be notified");
    ASSERT_TRUE(received_val == "Hello World", "Payload should match");
    return true;
}

// TEST 2: Verificar múltiples suscriptores para un mismo evento
bool test_multiple_subscribers() {
    EventBus bus;
    int count = 0;

    auto callback = [&](const EventPayload& p) { count++; };

    bus.subscribe("EVENT_A", callback);
    bus.subscribe("EVENT_A", callback);
    bus.subscribe("EVENT_A", callback);

    bus.publish("EVENT_A", std::string("Data"));

    wait_for_worker();

    ASSERT_TRUE(count == 3, "All three subscribers should be notified");
    return true;
}

// TEST 3: Verificar que eventos diferentes no se mezclen
bool test_event_isolation() {
    EventBus bus;
    bool notified_a = false;
    bool notified_b = false;

    bus.subscribe("EVENT_A", [&](const EventPayload& p) { notified_a = true; });
    bus.subscribe("EVENT_B", [&](const EventPayload& p) { notified_b = true; });

    bus.publish("EVENT_A", std::string("Data"));

    wait_for_worker();

    ASSERT_TRUE(notified_a == true, "Event A subscriber should be notified");
    ASSERT_TRUE(notified_b == false, "Event B subscriber should NOT be notified");
    return true;
}