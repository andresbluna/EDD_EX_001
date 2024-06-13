#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Jugador {
    char nombre[50];
    int juegos_jugados;
    int sustitucion;
    int min;
    int goles;
    struct Jugador* sig;
} Jugador;

Jugador* crear_jugador(const char* nombre, int juegos_jugados, int sustitucion, int min, int goles) {
    Jugador* nuevo_jugador = (Jugador*) malloc(sizeof(Jugador));
    if (nuevo_jugador == NULL) {
        fprintf(stderr, "No se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    strncpy(nuevo_jugador->nombre, nombre, 50 - 1);
    nuevo_jugador->nombre[50 - 1] = '\0';
    nuevo_jugador->juegos_jugados = juegos_jugados;
    nuevo_jugador->sustitucion = sustitucion;
    nuevo_jugador->min = min;
    nuevo_jugador->goles = goles;
    nuevo_jugador->sig = NULL;
    return nuevo_jugador;
}

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

    while (fgets(line, sizeof(line), file)) {
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
    }

    if (abajo!= NULL) {
        abajo->sig = principal;
    }

    fclose(file);
    return principal;
}

void imprimir_lista(Jugador* principal) {
    if (principal == NULL) {
        return;
    }

    Jugador* actual = principal;
    do {
        printf("Nombre: %s, Juegos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles: %d\n",
               actual->nombre, actual->juegos_jugados, actual->sustitucion, actual->min, actual->goles);
        actual = actual->sig;
    } while (actual!= principal);
}

void liberar_memoria_lista(Jugador* principal) {
    if (principal == NULL) {
        return;
    }

    Jugador* actual = principal;
    Jugador* sig_nodo;

    principal->sig = NULL;

    while (actual!= NULL) {
        sig_nodo = actual->sig;
        free(actual);
        actual = sig_nodo;
    }
}

int contar_vocales(const char* str) {
    int contador = 0;
    for (int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            contador++;
        }
    }
    return contador;
}

double calcular_porcentaje_vocales(Jugador* principal) {
    if (principal == NULL) {
        return 0.0;
    }

    int total_caracteres = 0;
    int total_vocales = 0;
    Jugador* actual = principal;

    do {
        total_caracteres += strlen(actual->nombre);
        total_vocales += contar_vocales(actual->nombre);
        actual = actual->sig;
    } while (actual!= principal);

    double porcentaje = (total_vocales * 100.0) / total_caracteres;
    return porcentaje;
}

double calcular_promedio(Jugador* principal, int (*obtener_valor)(Jugador*)) {
    if (principal == NULL) {
        return 0.0;
    }

    int total = 0;
    int count = 0;
    Jugador* actual = principal;

    do {
        total += obtener_valor(actual);
        count++;
        actual = actual->sig;
    } while (actual!= principal);

    return (count > 0)? (total / (double)count) : 0.0;
}

int obtener_goles(Jugador* jugador) {
    return jugador->goles;
}

int tamano_lista(Jugador* principal) {
    if (principal == NULL) {
        return 0;
    }
    int tamano = 1;
    Jugador* actual = principal->sig;
    while (actual!= principal) {
        tamano++;
        actual = actual->sig;
    }
    return tamano;
}

void imprimir_muestra(Jugador* principal, int indice) {
    if (principal == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    int tamano = tamano_lista(principal);
    if (indice < 0) {
        indice = tamano + indice; // Convertir índice negativo a positivo
    }

    // Calcular el índice efectivo dentro del rango de la lista circular
    indice %= tamano;

    Jugador* actual = principal;
    for (int i = 0; i < indice; i++) {
        actual = actual->sig;
    }

    printf("Informacion del jugador en el indice %d:\n", indice);
    printf("Nombre: %s, Juegos Jugados: %d, Sustituciones: %d, Minutos: %d, Goles: %d\n",
           actual->nombre, actual->juegos_jugados, actual->sustitucion, actual->min, actual->goles);
}

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

int main() {
    const char* nombredataprocess = "datafutbol_process.csv";
    Jugador* principal = leer_datafutbol_process(nombredataprocess);

    printf("Lista circular de los jugadores:\n");
    imprimir_lista(principal);

    double porcentaje_vocales = calcular_porcentaje_vocales(principal);
    printf("\nPorcentaje de vocales en los nombres de los jugadores: %.2f%%\n", porcentaje_vocales);

    double promedio_goles = calcular_promedio(principal, obtener_goles);
    printf("\nPromedio de goles: %.2f\n", promedio_goles);

    int indice;
    printf("Ingrese el indice del jugador que desea ver (puede ser negativo): ");
    scanf("%d", &indice);
    imprimir_muestra(principal, indice);

    printf("Ordenando la lista por goles...\n");
    ordenar_lista(principal, 4); // Ordenar por goles
    printf("Lista ordenada:\n");
    imprimir_lista(principal);

    liberar_memoria_lista(principal);
    return 0;
}