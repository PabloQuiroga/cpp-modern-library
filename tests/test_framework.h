//
// Created by Pablo Quiroga on 09/10/2026.
//

#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>

// Variable global para rastrear fallos
extern int total_failed_tests;

#define ASSERT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            std::cout << "  ❌ FAIL: " << message << std::endl; \
            total_failed_tests++; \
            return false; \
        } \
    } while (0)

#define RUN_TEST(test_func) \
    do { \
        std::cout << "Running " << #test_func << "... "; \
        if (test_func()) { \
            std::cout << "✅ PASS" << std::endl; \
        } else { \
            std::cout << "❌ FAIL" << std::endl; \
        } \
    } while (0)

#endif
