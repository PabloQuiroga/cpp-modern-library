//
// Created by Pablo Quiroga on 08/10/2026.
//
#include <iostream>
#include "../tests/test_framework.h"

bool test_single_subscriber();
bool test_multiple_subscribers();
bool test_event_isolation();

int main() {
    std::cout << "=== RUNNING EVENT BUS UNIT TESTS ===\n";

    RUN_TEST(test_single_subscriber);
    RUN_TEST(test_multiple_subscribers);
    RUN_TEST(test_event_isolation);

    std::cout << "====================================\n";

    return 0;
}
