#include "loader_data.py"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Definimos la estructura del Nodo y puntero al siguiente nodo
    typedef struct Jugador{
        char nombre[50];
        int juegos_jugados;
        int sustitucion;
        int min;
        int goles;
        struct Jugador* sig;
    } Jugador;


//funcion para crear nuevo nodo por jugador

Jugador* crear_jugador(const char* nombre, int juegos_jugados, int sustitucion, int min, int goles) {
    Jugador* nuevo_jugador = (Jugador*) malloc(sizeof (Jugador));
    if(nuevo_jugador == NULL) {
        fprintf(stderr, "No se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    strncpy(nuevo_jugador ->nombre,nombre, 50 -1);
    nuevo_jugador -> juegos_jugados = juegos_jugados;
    nuevo_jugador -> min = min;
    nuevo_jugador -> goles = goles;
    nuevo_jugador -> sig = NULL;
    return nuevo_jugador;
}


//funcion que lee archivo y crea la lista circular

Jugador* leer_datafutbol_process(const char* nombredataprocess) {
    FILE *file = fopen(nombredataprocess, "r");
    if (file == NULL) {
        fprintf(stderr, "No fue posible leer la data\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    Jugador *principal = NULL;
    Jugador *abajo = NULL;

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file));
    char nombre[50];
    int juegos_jugados, sustitucion, min, goles;

    sscanf(line, "%49[^,],%d,%d,%d,%d", nombre, &juegos_jugados, &sustitucion, &min, &goles);

    Jugador *nuevo_jugador = crear_jugador(nombre, juegos_jugados, sustitucion, min, goles);

    if (principal == NULL) {
        principal = nuevo_jugador;
        abajo = nuevo_jugador;
    } else {
        abajo->sig = nuevo_jugador;
        abajo = nuevo_jugador;
    }
    if (principal != NULL) {
        abajo -> sig = principal;
}
    fclose(file);
    return principal;

}

//funcion para imprimir la lista

void imprimir_lista (Jugador* principal) {
    if (principal == NULL){
        return;
    }

    Jugador* actual = principal;
    do {
        printf("nombre: %s, Juegos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles %d\n",
               actual->nombre, actual->juegos_jugados, actual->sustitucion, actual->min, actual->goles);
        actual = actual->sig;
    } while (actual != principal);

}

//funcion para liberar memoria de lista
void liberar_memoria_lista(Jugador* principal) {
    if (principal == NULL) {
        return;
    }

    Jugador* actual = principal;
    Jugador* sig_nodo;


    principal->sig = NULL;

    while (actual != NULL) {
        sig_nodo = actual->sig;
        free(actual);
        actual = sig_nodo;
    }
}


//funcion pricipal

int main() {
    const char* nombredataprocess = "datafutbol.csv";
    Jugador* principal = leer_datafutbol_process(nombredataprocess);

    printf("Lista circular de los jugadores:\n");
    imprimir_lista(principal);
    liberar_memoria_lista(principal);
    return 0;
}