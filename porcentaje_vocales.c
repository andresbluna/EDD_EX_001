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


double porcentaje_vocales = calcular_porcentaje_vocales(principal);
printf("\nPorcentaje de vocales en los nombres de los jugadores: %.2f%%\n", porcentaje_vocales);