# Plan de Implementación: Event Bus en C++ Moderno

## 1. Tecnologías y Herramientas
- **Lenguaje**: C++17 o superior.
- **Gestión de Memoria**: Uso de `std::unique_ptr` y `std::shared_ptr` para evitar memory leaks.
- **Contenedores STL**:
    - `std::unordered_map`: Para el mapa de suscriptores (Acceso $O(1)$).
    - `std::vector` o `std::list`: Para almacenar la colección de callbacks por evento.
- **Funciones Genéricas**: `std::function` y `std::any` para permitir que los callbacks y los payloads sean de cualquier tipo.

## 2. Definición de la API Técnica

### 2.1 Tipos de Datos
- `EventType`: Un alias de `std::string` para identificar los eventos.
- `EventPayload`: Uso de `std::any` para permitir cualquier tipo de dato como carga útil.
- `Callback`: Un alias de `std::function<void(std::any)>`.

### 2.2 Interfaz de la Clase `EventBus`
- `void subscribe(const EventType& type, Callback callback)`
    - Agrega la función al vector asociado a la clave en el `unordered_map`.
- `void publish(const EventType& type, std::any payload)`
    - Busca el vector de callbacks y ejecuta cada función pasando el payload.
- `void unsubscribe(const EventType& type, Callback callback)`
    - Elimina el callback específico de la lista.

## 3. Implementación de la Asincronía
Para cumplir con la especificación de no bloquear al publicador, implementaremos:
1. **`std::queue`**: Una cola para almacenar los eventos pendientes.
2. **`std::mutex` y `std::condition_variable`**: Para asegurar que la cola sea segura para múltiples hilos (*thread-safe*).
3. **`std::thread`**: Un hilo dedicado (Worker) que procese la cola en bucle.

## 4. Estrategia de Validación
- **Tests Unitarios**: Implementación de una suite de tests que verifique:
    - Notificación múltiple de suscriptores.
    - Manejo de payloads de diferentes tipos (int, string, structs).
    - Estabilidad al eliminar suscriptores mientras se publica un evento.
- **Análisis de Memoria**: Validación con Valgrind para asegurar que los `shared_ptr` estén liberando la memoria correctamente.