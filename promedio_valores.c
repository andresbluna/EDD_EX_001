#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo* sig;
} Nodo;

// Función para crear un nuevo nodo
Nodo* crear_nodo(int valor) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    nuevo_nodo->valor = valor;
    nuevo_nodo->sig = NULL;
    return nuevo_nodo;
}

// Función para calcular el promedio de los valores en la lista circular
double calcular_promedio(Nodo* inicio) {
    if (inicio == NULL) {
        return 0.0; // Lista vacía
    }

    Nodo* actual = inicio;
    int suma = 0;
    int contador = 0;

    do {
        suma += actual->valor;
        contador++;
        actual = actual->sig;
    } while (actual != inicio);

    return (double)suma / contador;
}

int main() {
    // Crear una lista circular de ejemplo
    Nodo* nodo1 = crear_nodo(10);
    Nodo* nodo2 = crear_nodo(20);
    Nodo* nodo3 = crear_nodo(30);

    nodo1->sig = nodo2;
    nodo2->sig = nodo3;
    nodo3->sig = nodo1; // Hacer la lista circular

    // Calcular el promedio
    double promedio = calcular_promedio(nodo1);
    printf("El promedio de los valores en la lista circular es: %.2f\n", promedio);

    // Liberar memoria (no olvides liberar todos los nodos)
    free(nodo1);
    free(nodo2);
    free(nodo3);

    return 0;
}
