// Función para particionar la lista para QuickSort
Jugador* particion(Jugador* inicio, Jugador* fin) {
    int pivot = fin->juegos_jugados;
    Jugador* i = inicio->ant;

    for (Jugador* j = inicio; j != fin; j = j->sig) {
        if (j->juegos_jugados <= pivot) {
            i = (i == NULL) ? inicio : i->sig;
            // Intercambiar los nodos i y j
            // (nombre, juegos_jugados, sustitucion, min, goles)
            // ...
        }
    }

    i = (i == NULL) ? inicio : i->sig;
    // Intercambiar los nodos i y fin
    // (nombre, juegos_jugados, sustitucion, min, goles)
    // ...

    return i;
}

// Función QuickSort recursiva
void quicksort(Jugador* inicio, Jugador* fin) {
    if (fin != NULL && inicio != fin && inicio != fin->sig) {
        Jugador* pivot = particion(inicio, fin);
        quicksort(inicio, pivot->ant);
        quicksort(pivot->sig, fin);
    }
}