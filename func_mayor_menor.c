//jugador* juegos_jugados
// Función para intercambiar dos nodos (jugadores)
void intercambiar_nodos(Jugador* a, Jugador* b) {
    Jugador temp = *a;
    *a = *b;
    *b = temp;
}

// Función para ordenar la lista de jugadores de menor a mayor según los juegos jugados
void ordenar_por_cualquier_dato_del_nodo(Jugador* inicio) {
    if (inicio == NULL) {
        return; // Lista vacía
    }

    int intercambiado;
    Jugador* actual;
    Jugador* ultimo = NULL;

    do {
        intercambiado = 0;
        actual = inicio;

        while (actual->sig != ultimo) {
            if (actual->juegos_jugados > actual->sig->juegos_jugados) {
                intercambiar_nodos(actual, actual->sig);
                intercambiado = 1;
            }
            actual = actual->sig;
        }
        ultimo = actual;
    } while (intercambiado);
}

// Llama a esta función pasando el puntero al primer jugador de la lista
// antes de imprimir la lista o liberar la memoria.

// Ejemplo de uso:
// Jugador* principal = leer_datafutbol_process("datafutbol_process.csv");
// ordenar_por_juegos_jugados(principal);
// imprimir_lista(principal);
// liberar_memoria_lista(principal);
