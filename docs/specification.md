# Especificación: Bus de Eventos Asíncronos

## 1. Objetivo
Implementar un sistema centralizado (Event Bus) que permita a diferentes componentes de una aplicación comunicarse entre sí sin estar estrechamente acoplados. El sistema debe permitir que los componentes se suscriban a tipos de eventos específicos y reaccionen cuando dichos eventos sean publicados.

## 2. Requerimientos Funcionales

### 2.1 Capacidades Core
- **Suscripción a Eventos**: Los componentes deben poder registrar una función de respuesta (callback) para un identificador de evento específico.
- **Publicación de Eventos**: El sistema debe permitir que cualquier componente dispare un evento. Cuando se publica un evento, todos los componentes suscritos a ese evento específico deben ser notificados.
- **Cargas Útiles Genéricas (Payloads)**: Los eventos deben poder transportar datos de cualquier tipo, permitiendo que el suscriptor reciba la información asociada al evento.
- **Anulación mediante token/ID**: El sistema debe proporcionar un identificador único (Token) al momento de la suscripción, el cual será requerido para procesar la anulación de la misma.

### 2.2 Restricciones de Comportamiento
- **Desacoplamiento**: El publicador de un evento no debe conocer quiénes son los suscriptores, ni cuántos hay.
- **Orden de Ejecución**: El sistema debe garantizar que todos los suscriptores sean notificados, independientemente del orden de suscripción.
- **Potencial Asíncrono**: El diseño debe permitir que el manejo de los eventos ocurra en hilos de ejecución diferentes sin bloquear al publicador principal.

## 3. Requerimientos No Funcionales

### 3.1 Rendimiento
- **Suscripción/Anulación**: Debe ser una operación de tiempo constante $O(1)$.
- **Publicación**: El tiempo para notificar a los suscriptores debe ser proporcional al número de suscriptores de ese evento específico, no al total de eventos del sistema.

### 3.2 Fiabilidad
- **Robustez**: Un fallo o error en la función de respuesta de un suscriptor no debe impedir que los demás suscriptores reciban el evento.
- **Gestión del Ciclo de Vida**: El sistema debe asegurar que no se intenten llamar a suscriptores que ya no existen (evitando referencias colgantes).

## 4. Criterios de Éxito
El sistema se considera exitoso si:
1. Componentes totalmente independientes pueden comunicarse mediante eventos.
2. Añadir un nuevo tipo de evento no requiere modificar la lógica central del Event Bus.
3. El sistema permanece estable bajo una alta frecuencia de publicaciones.