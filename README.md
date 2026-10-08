# Librería de Bus de Eventos en C++ Moderno

## 🚀 Descripción General
Esta librería implementa un **Bus de Eventos** asíncrono utilizando C++ moderno (C++17). Permite que diferentes componentes de una aplicación se comuniquen a través de eventos sin estar estrechamente acoplados, siguiendo los patrones de diseño Observer y Adapter.

## 🎯 Objetivos de Ingeniería
El objetivo principal de este proyecto es demostrar prácticas avanzadas de ingeniería de software, incluyendo:
- **Genericidad Segura**: Uso de `std::any` para manejar cargas útiles (payloads) de cualquier tipo.
- **Procesamiento Asíncrono**: Implementación del patrón Productor-Consumidor con un hilo de trabajo dedicado para evitar el bloqueo del flujo principal.
- **Seguridad de Memoria**: Uso estricto de punteros inteligentes (`std::unique_ptr`, `std::shared_ptr`) para eliminar las fugas de memoria.
- **Rendimiento O(1)**: Gestión eficiente de suscriptores mediante mapas de hash para búsquedas en tiempo constante.

## 🛠 Stack Técnico
- **Lenguaje**: C++17
- **Sistema de Construcción**: CMake
- **CI/CD**: GitHub Actions
- **Validación**: Unit Testing y Análisis de Memoria (Valgrind/Leaks)

## 📖 Documentación del Proyecto
Este proyecto sigue un proceso estricto de **Desarrollo Basado en Especificaciones (SDD)**. Todos los detalles técnicos se encuentran en la carpeta `/docs`:
- [Especificación](docs/specification.md): Requerimientos funcionales y no funcionales.
- [Diseño Lógico](docs/logic_design.md): Flujo algorítmico y modelo de datos.
- [Plan de Implementación](docs/implementation_plan.md): Traducción técnica a C++.
- [Decisiones de Arquitectura](docs/decisions/): Registro de decisiones técnicas críticas (ADRs).

## 🚀 Inicio Rápido
### Construcción y Ejecución
```bash
mkdir build && cd build
cmake ..
make
./event_bus_app
```
## 🛡 Aseguramiento de Calidad

Cada commit es validado por un pipeline de CI que garantiza que:
1. El código compila bajo el estándar C++17.
2. Todas las pruebas unitarias pasan exitosamente.
3. No existen fugas de memoria.