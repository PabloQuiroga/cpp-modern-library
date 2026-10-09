//
// Created by Pablo Quiroga on 08/10/2026.
//
#include <iostream>
#include "../tests/test_framework.h"

bool test_single_subscriber();
bool test_multiple_subscribers();
bool test_event_isolation();

// Definimos la variable global de fallos
int total_failed_tests = 0;

int main() {
    std::cout << "=== RUNNING EVENT BUS UNIT TESTS ===\n";

    RUN_TEST(test_single_subscriber);
    RUN_TEST(test_multiple_subscribers);
    RUN_TEST(test_event_isolation);

    std::cout << "====================================\n";

    if (total_failed_tests > 0) {
        std::cout << "FAILED: " << total_failed_tests << " tests failed." << std::endl;
        return 1; // <--- ESTO es lo que la CI usa para poner la X roja
    }

    std::cout << "ALL TESTS PASSED SUCCESSFULLY!" << std::endl;
    return 0;
}
