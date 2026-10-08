# Diseño Lógico: Bus de Eventos Asíncronos

## 1. Modelo de Datos Lógico
Para gestionar las suscripciones, el sistema utilizará una estructura de **Mapa de Listas**:

- **Clave (Key)**: Un identificador único para el evento (ej: "USER_LOGIN").
- **Valor (Value)**: Una colección de referencias a funciones (callbacks) que deben ejecutarse.

**Flujo de datos:**
`Evento` $\rightarrow$ `Hash del Evento` $\rightarrow$ `Lista de Suscriptores` $\rightarrow$ `Ejecución de Callbacks`

## 2. Algoritmos de Operación

### 2.1 Proceso de Suscripción
1. El componente proporciona un `Identificador de Evento` y una `Función de Respuesta`.
2. El sistema busca el identificador en el Mapa.
3. Si el identificador ya existe, añade la función a la lista de suscriptores.
4. Si no existe, crea una nueva entrada en el mapa y añade la función como el primer suscriptor.

### 2.2 Proceso de Publicación (El disparador)
1. El publicador envía un `Identificador de Evento` y una `Carga Útil (Payload)`.
2. El sistema localiza la lista de suscriptores asociada a ese identificador.
3. Si la lista existe, el sistema recorre la colección y ejecuta cada función de respuesta, pasándole la carga útil como argumento.
4. Si la lista está vacía o el evento no existe, la operación termina silenciosamente sin error.

### 2.3 Proceso de Anulación
1. El componente proporciona el `Identificador de Evento` y la referencia a la `Función de Respuesta` que desea eliminar.
2. El sistema localiza la lista de suscriptores del evento.
3. Elimina la función específica de la lista.
4. Si la lista queda vacía, el sistema puede eliminar la entrada del mapa para ahorrar memoria.

## 3. Estrategia de Asincronía
Para evitar que el publicador se bloquee mientras los suscriptores procesan el evento, se propone el siguiente flujo lógico:
1. El evento es publicado y colocado en una **Cola de Eventos** (Event Queue).
2. Un **Hilo de Procesamiento** (Worker Thread) monitorea la cola.
3. El Worker extrae el evento y notifica a los suscriptores en segundo plano.