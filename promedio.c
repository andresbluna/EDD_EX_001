//
// Created by Fernando G on 13-06-2024.
//
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

double promedio_goles = calcular_promedio(principal, obtener_goles);
printf("\nPromedio de goles: %.2f\n", promedio_goles);