#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicion estructura nodo y siguiente nodo
typedef struct Jugador {
    char nombre[50];
    int juegos_jugados;
    int sustitucion;
    int min;
    int goles;
    struct Jugador* sig;
    struct Jugador* ant;
} Jugador;

// Función para crear nuevo nodo por jugador
Jugador* crear_jugador(const char* nombre, int juegos_jugados, int sustitucion, int min, int goles) {
    Jugador* nuevo_jugador = (Jugador*) malloc(sizeof(Jugador));
    if (nuevo_jugador == NULL) {
        fprintf(stderr, "No se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    strncpy(nuevo_jugador->nombre, nombre, 50 - 1);
    nuevo_jugador->nombre[50 - 1] = '\0'; // Asegurar que la cadena esté terminada en nulo
    nuevo_jugador->juegos_jugados = juegos_jugados;
    nuevo_jugador->sustitucion = sustitucion;
    nuevo_jugador->min = min;
    nuevo_jugador->goles = goles;
    nuevo_jugador->sig = NULL;
    nuevo_jugador->ant = NULL;
    return nuevo_jugador;
}

// Función que lee archivo y crea la lista circular
Jugador* leer_datafutbol_process(const char* nombredataprocess) {
    FILE *file = fopen(nombredataprocess, "r");
    if (file == NULL) {
        fprintf(stderr, "No fue posible leer la data\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    Jugador *principal = NULL;
    Jugador *abajo = NULL;

    // Leer la cabecera
    fgets(line, sizeof(line), file);

    // Leer cada línea del archivo
    while (fgets(line, sizeof(line), file)) {
        char nombre[50];
        int juegos_jugados, sustitucion, min, goles;

        // Parsear la línea
        sscanf(line, "%49[^,],%d,%d,%d,%d", nombre, &juegos_jugados, &sustitucion, &min, &goles);

        // Crear un nuevo nodo
        Jugador *nuevo_jugador = crear_jugador(nombre, juegos_jugados, sustitucion, min, goles);

        // Insertar el nodo en la lista circular
        if (principal == NULL) {
            principal = nuevo_jugador;
            abajo = nuevo_jugador;
        } else {
            abajo->sig = nuevo_jugador;
            nuevo_jugador->ant = abajo;
            abajo = nuevo_jugador;
        }
    }

    // Hacer la lista circular
    if (abajo != NULL) {
        abajo->sig = principal;
        principal->ant=abajo;
    }

    fclose(file);
    return principal;
}

// Función para imprimir la lista
void imprimir_lista(Jugador* principal) {
    if (principal == NULL) {
        return;
    }

    Jugador* actual = principal;
    do {
        printf("Nombre: %s, Juegos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles: %d\n",
               actual->nombre, actual->juegos_jugados, actual->sustitucion, actual->min, actual->goles);
        actual = actual->sig;
    } while (actual != principal);
}

// Función para liberar memoria de la lista
void liberar_memoria_lista(Jugador* principal) {
    if (principal == NULL) {
        return;
    }

    Jugador* actual = principal;
    Jugador* sig_nodo;

    // Romper el ciclo para poder liberar la memoria
    principal->sig = NULL;

    while (actual != NULL) {
        sig_nodo = actual->sig;
        free(actual);
        actual = sig_nodo;
    }
}

// Función principal
int main() {
    const char* nombredataprocess = "datafutbol_process.csv";
    Jugador* principal = leer_datafutbol_process(nombredataprocess);

    printf("Lista circular de los jugadores:\n");
    imprimir_lista(principal);
    liberar_memoria_lista(principal);
    return 0;
}