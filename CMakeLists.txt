cmake_minimum_required(VERSION 3.20)
project(cpp_modern_library CXX)

# Usamos C++17 para tener acceso a std::any y std::optional
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Por ahora, solo creamos el ejecutable con el main
add_executable(
        event_bus_app
        src/main.cpp
)