#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura para el nodo Jugador
typedef struct Jugador {
    char nombre[50];
    int juegos_jugados;
    int sustitucion;
    int min;
    int goles;
    struct Jugador* sig;
    struct Jugador* ant;
} Jugador;

// Función para crear un nuevo nodo Jugador
Jugador* crear_jugador(const char* nombre, int juegos_jugados, int sustitucion, int min, int goles) {
    Jugador* nuevo_jugador = (Jugador*)malloc(sizeof(Jugador));
    if (nuevo_jugador == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
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

// Función para calcular el promedio de los valores en la lista circular doblemente enlazada
double calcular_promedio(Jugador* inicio) {
    if (inicio == NULL) {
        return 0.0; // Lista vacía
    }

    Jugador* actual = inicio;
    int suma = 0;
    int contador = 0;

    do {
        suma += actual->goles; // Sumar los goles (puedes cambiar esto según lo que necesites)
        contador++;
        actual = actual->sig;
    } while (actual != inicio);

    return (double)suma / contador;
}

int main() {
    // Aquí debes leer los datos del archivo CSV y crear la lista circular doblemente enlazada
    // Luego, llama a la función calcular_promedio con el puntero al primer jugador de la lista

    // Ejemplo de uso:
    Jugador* principal = crear_jugador("Lionel Messi", 10, 2, 900, 15);
    double promedio = calcular_promedio(principal);
    printf("El promedio de los goles es: %.2f\n", promedio);

    // Liberar memoria (no olvides liberar todos los nodos)

    return 0;
}

