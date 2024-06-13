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

int indice;
printf("Ingrese el indice del jugador que desea ver (puede ser negativo): ");
scanf("%d", &indice);
imprimir_muestra(principal, indice);