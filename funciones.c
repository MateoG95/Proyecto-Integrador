#include <stdio.h>
#include <string.h>
#include "funciones.h"

void inicializarZonas(struct Zona zonas[], int *totalZonas) {
    *totalZonas = 5;
    strcpy(zonas[0].nombre, "Centro");
    strcpy(zonas[1].nombre, "Norte");
    strcpy(zonas[2].nombre, "Sur");
    strcpy(zonas[3].nombre, "Este");
    strcpy(zonas[4].nombre, "Oeste");

    for (int i = 0; i < *totalZonas; i++) {
        for (int j = 0; j < 30; j++) {
            zonas[i].historico[j] = 0;
        }
        zonas[i].actual = 0;
        zonas[i].prediccion = 0;
    }
}

void registrarContaminacion(struct Zona zonas[], int totalZonas) {
    for (int i = 0; i < totalZonas; i++) {
        printf("Ingrese nivel de contaminacion actual en zona %s: ", zonas[i].nombre);
        scanf("%f", &zonas[i].actual);
        // Desplazar los historicos
        for (int j = 29; j > 0; j--) {
            zonas[i].historico[j] = zonas[i].historico[j - 1];
        }
        zonas[i].historico[0] = zonas[i].actual;
    }
}

void calcularPromedios(struct Zona zonas[], int totalZonas) {
    for (int i = 0; i < totalZonas; i++) {
        float suma = 0;
        for (int j = 0; j < 30; j++) {
            suma += zonas[i].historico[j];
        }
        float promedio = suma / 30.0;
        printf("Promedio en zona %s: %.2f ug/m3\n", zonas[i].nombre, promedio);
        if (promedio > 25.0) {
            printf("Advertencia: promedio supera limite OMS en %s.\n", zonas[i].nombre);
        }
    }
}

void predecirContaminacion(struct Zona zonas[], int totalZonas, struct Clima clima) {
    for (int i = 0; i < totalZonas; i++) {
        float peso = 0, suma = 0;
        for (int j = 0; j < 5; j++) {
            suma += zonas[i].historico[j] * (5 - j);
            peso += (5 - j);
        }
        zonas[i].prediccion = suma / peso;

        // Ajuste climático simple
        if (clima.viento < 5.0) zonas[i].prediccion += 5.0;
        if (clima.humedad > 70.0) zonas[i].prediccion += 2.0;
        if (clima.temperatura > 30.0) zonas[i].prediccion += 1.0;

        printf("Prediccion para zona %s: %.2f ug/m3\n", zonas[i].nombre, zonas[i].prediccion);
    }
}

void generarAlertas(struct Zona zonas[], int totalZonas) {
    for (int i = 0; i < totalZonas; i++) {
        if (zonas[i].prediccion > 25.0) {
            printf("ALERTA: Se preve alta contaminacion en zona %s. Prediccion: %.2f ug/m3\n",
                   zonas[i].nombre, zonas[i].prediccion);
        }
    }
}

void generarRecomendaciones(struct Zona zonas[], int totalZonas) {
    for (int i = 0; i < totalZonas; i++) {
        if (zonas[i].prediccion > 25.0) {
            printf("Recomendaciones para zona %s:\n", zonas[i].nombre);
            printf("- Reducir trafico vehicular\n");
            printf("- Suspender actividades al aire libre\n");
            printf("- Restringir emisiones industriales\n");
        }
    }
}

void exportarDatos(struct Zona zonas[], int totalZonas) {
    FILE *f = fopen("reporte_contaminacion.txt", "w");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(f, "REPORTE DE CONTAMINACION DEL AIRE - SIGPCA\n\n");
    for (int i = 0; i < totalZonas; i++) {
        fprintf(f, "Zona: %s\n", zonas[i].nombre);
        fprintf(f, "Actual: %.2f ug/m3\n", zonas[i].actual);
        fprintf(f, "Prediccion: %.2f ug/m3\n", zonas[i].prediccion);
        fprintf(f, "Historico 30 dias: ");
        for (int j = 0; j < 30; j++) {
            fprintf(f, "%.1f ", zonas[i].historico[j]);
        }
        fprintf(f, "\n----------------------------------------\n");
    }

    fclose(f);
    printf("Datos exportados en 'reporte_contaminacion.txt'\n");
}
