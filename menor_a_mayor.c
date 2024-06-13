//
// Created by Fernando G on 13-06-2024.
//
// Función para intercambiar los datos entre dos nodos
void intercambiar_datos(Jugador* a, Jugador* b) {
    char temp_nombre[50];
    strcpy(temp_nombre, a->nombre);
    strcpy(a->nombre, b->nombre);
    strcpy(b->nombre, temp_nombre);

    int temp_juegos_jugados = a->juegos_jugados;
    a->juegos_jugados = b->juegos_jugados;
    b->juegos_jugados = temp_juegos_jugados;

    int temp_sustitucion = a->sustitucion;
    a->sustitucion = b->sustitucion;
    b->sustitucion = temp_sustitucion;

    int temp_min = a->min;
    a->min = b->min;
    b->min = temp_min;

    int temp_goles = a->goles;
    a->goles = b->goles;
    b->goles = temp_goles;
}

// Función para ordenar la lista de jugadores de mayor a menor según un parámetro específico
void ordenar_lista(Jugador* principal, int parametro) {
    if (principal == NULL || principal->sig == principal) {
        return; // La lista está vacía o solo tiene un elemento
    }

    int ordenado = 0;
    while (!ordenado) {
        ordenado = 1; // Suponemos que la lista está ordenada hasta que encontremos lo contrario
        Jugador* actual = principal;
        Jugador* siguiente = principal->sig;

        while (siguiente!= principal) {
            switch (parametro) {
                case 1:
                    if (actual->juegos_jugados < siguiente->juegos_jugados) {
                        intercambiar_datos(actual, siguiente);
                        ordenado = 0;
                    }
                    break;
                case 2:
                    if (actual->sustitucion < siguiente->sustitucion) {
                        intercambiar_datos(actual, siguiente);
                        ordenado = 0;
                    }
                    break;
                case 3:
                    if (actual->min < siguiente->min) {
                        intercambiar_datos(actual, siguiente);
                        ordenado = 0;
                    }
                    break;
                case 4:
                    if (actual->goles < siguiente->goles) {
                        intercambiar_datos(actual, siguiente);
                        ordenado = 0;
                    }
                    break;
                default:
                    printf("Parámetro inválido para ordenar.\n");
                    return;
            }
            actual = siguiente;
            siguiente = siguiente->sig;
        }
    }
}

printf("Ordenando la lista por goles...\n");
ordenar_lista(principal, 2); // Ordenar por goles
printf("Lista ordenada:\n");
imprimir_lista(principal);
