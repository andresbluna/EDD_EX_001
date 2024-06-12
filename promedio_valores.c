// Función para calcular el promedio de los goles en la lista doblemente enlazada
double calcular_promedio_goles(Jugador* inicio) {
    if (inicio == NULL) {
        return 0.0; // Lista vacía
    }

    Jugador* actual = inicio;
    int suma_goles = 0;
    int contador = 0;

    do {
        suma_goles += actual->goles;
        contador++;
        actual = actual->sig;
    } while (actual != inicio);

    return (double)suma_goles / contador;
}
double promedio_goles = calcular_promedio_goles(principal);
printf("El promedio de goles es: %.2f\n", promedio_goles);
