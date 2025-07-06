#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu() {
    int opc;
    printf("\n--- SIGPCA: Sistema Integral de Gestion y Prediccion de Contaminacion del Aire ---\n");
    printf("1. Inicializar datos zonas\n"); 
    printf("2. Registrar niveles actuales de contaminacion Quito (todas las zonas)\n");
    printf("3. Registrar niveles actuales de contaminacion por zona\n");
    printf("4. Calcular promedios historicos (por zona o total)\n");
    printf("5. Predecir niveles de contaminacion (por zona o total)\n");
    printf("6. Generar alertas preventivas\n");
    printf("7. Generar recomendaciones (por zona o total)\n");
    printf("8. Editar datos Contaminacion\n");
    printf("9. Exportar datos del sistema\n");
    printf("10. Salir\n"); 
    printf("Seleccione una opcion: ");
    scanf("%d", &opc);
    return opc;
}


void cargarDatosDesdeTXT(struct Zona *zona, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        return;
    }

    int contador = 0;
    while (fscanf(archivo, "%f", &zona->historico[0][contador]) == 1 && contador < 30) {
        contador++;
    }

    fclose(archivo);
}

void inicializarZonas(struct Zona zonas[], int *totalZonas) {
    const char *nombres[] = {"Centro", "Cotocollao", "Carapungo", "Belisario", "Sur"};
    *totalZonas = 5;

    for (int i = 0; i < *totalZonas; i++) {
        strcpy(zonas[i].nombre, nombres[i]);
        for (int j = 0; j < 4; j++) {
            zonas[i].actual[j] = 0;
            zonas[i].prediccion[j] = 0;
            for (int k = 0; k < 30; k++) {
                zonas[i].historico[j][k] = 0;
            }
        }
    }
}

void registrarContaminacionPorZona(struct Zona zonas[], int totalZonas) {
    int zonaIndex, elemento;
    printf("Seleccione zona (0 a %d): ", totalZonas - 1);
    scanf("%d", &zonaIndex);

    if (zonaIndex < 0 || zonaIndex >= totalZonas) {
        printf("Zona invalida.\n");
        return;
    }

    printf("Seleccione contaminante:\n");
    printf("1. PM2.5\n2. CO2\n3. NO2\n4. SO2\nOpcion: ");
    scanf("%d", &elemento);
    if (elemento < 1 || elemento > 4) {
        printf("Contaminante invalido.\n");
        return;
    }

    int idx = elemento - 1;
    float valor;
    printf("Ingrese valor actual de contaminacion: ");
    scanf("%f", &valor);

    zonas[zonaIndex].actual[idx] = valor;

    for (int j = 29; j > 0; j--) {
        zonas[zonaIndex].historico[idx][j] = zonas[zonaIndex].historico[idx][j - 1];
    }
    zonas[zonaIndex].historico[idx][0] = valor;

    printf("Registro exitoso en %s para contaminante %d.\n", zonas[zonaIndex].nombre, elemento);
}


void calcularPromedios(struct Zona zonas[], int totalZonas, int soloUnaZona) {
    int inicio = 0, fin = totalZonas;

    if (soloUnaZona) {
        printf("Seleccione zona (0 a %d): ", totalZonas - 1);
        scanf("%d", &inicio);
        fin = inicio + 1;
    }

    const char *nombres[] = {"PM2.5", "CO2", "NO2", "SO2"};

    for (int i = inicio; i < fin; i++) {
        printf("Promedios historicos en zona %s:\n", zonas[i].nombre);
        for (int j = 0; j < 4; j++) {
            float suma = 0;
            for (int k = 0; k < 30; k++) {
                suma += zonas[i].historico[j][k];
            }
            printf("%s: %.2f ug/m3\n", nombres[j], suma / 30.0);
        }
        printf("\n");
    }
}

void predecirContaminacion(struct Zona zonas[], int totalZonas, struct Clima clima, int soloUnaZona) {
    int inicio = 0, fin = totalZonas;

    if (soloUnaZona) {
        printf("Seleccione zona (0 a %d): ", totalZonas - 1);
        scanf("%d", &inicio);
        fin = inicio + 1;
    }

    for (int i = inicio; i < fin; i++) {
        for (int e = 0; e < 4; e++) {
            float peso = 0, suma = 0;
            for (int j = 0; j < 5; j++) {
                suma += zonas[i].historico[e][j] * (5 - j);
                peso += (5 - j);
            }
            zonas[i].prediccion[e] = suma / peso;

            if (clima.viento < 5.0) zonas[i].prediccion[e] += 5.0;
            if (clima.humedad > 70.0) zonas[i].prediccion[e] += 2.0;
            if (clima.temperatura > 30.0) zonas[i].prediccion[e] += 1.0;
        }

        printf("Predicciones en zona %s:\n", zonas[i].nombre);
        printf("PM2.5: %.2f, CO2: %.2f, NO2: %.2f, SO2: %.2f\n",
               zonas[i].prediccion[0], zonas[i].prediccion[1],
               zonas[i].prediccion[2], zonas[i].prediccion[3]);
    }
}

void predecirPorZona(struct Zona zonas[], int totalZonas, struct Clima clima) {
    int index;
    printf("Seleccione zona a predecir (0-%d); 0:Centro 1:Cotocollao 2:Carapungo 3:Belisario 4:Sur: ", totalZonas - 1);
    scanf("%d", &index);

    if (index < 0 || index >= totalZonas) {
        printf("Zona invalida.\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        float suma = 0, peso = 0;
        for (int j = 0; j < 5; j++) {
            suma += zonas[index].historico[i][j] * (5 - j);
            peso += (5 - j);
        }
        zonas[index].prediccion[i] = suma / peso;

        if (clima.viento < 5.0) zonas[index].prediccion[i] += 5.0;
        if (clima.humedad > 70.0) zonas[index].prediccion[i] += 2.0;
        if (clima.temperatura > 30.0) zonas[index].prediccion[i] += 1.0;
    }

    printf("Predicciones para zona %s:\n", zonas[index].nombre);
    printf("PM2.5: %.2f, CO2: %.2f, NO2: %.2f, SO2: %.2f\n",
           zonas[index].prediccion[0], zonas[index].prediccion[1],
           zonas[index].prediccion[2], zonas[index].prediccion[3]);
}

void generarAlertas(struct Zona zonas[], int totalZonas, int soloUnaZona) {
    float limites[4] = {25.0, 50.0, 30.0, 20.0};
    const char *nombres[] = {"PM2.5", "CO2", "NO2", "SO2"};

    int inicio = 0, fin = totalZonas;

    if (soloUnaZona) {
        printf("Seleccione zona (0 a %d): ", totalZonas - 1);
        scanf("%d", &inicio);
        if (inicio < 0 || inicio >= totalZonas) {
            printf("Zona invalida.\n");
            return;
        }
        fin = inicio + 1;
    }

    for (int i = inicio; i < fin; i++) {
        int alertaMostrada = 0;
        for (int j = 0; j < 4; j++) {
            if (zonas[i].prediccion[j] > limites[j]) {
                if (!alertaMostrada) {
                    printf("\n>>> ALERTAS PARA ZONA %s <<<\n", zonas[i].nombre);
                    alertaMostrada = 1;
                }
                printf("• %s supera limite (%.2f > %.2f ug/m3)\n", nombres[j], zonas[i].prediccion[j], limites[j]);
            }
        }
        if (!alertaMostrada) {
            printf("Zona %s sin alertas.\n", zonas[i].nombre);
        }
    }
}



void generarRecomendaciones(struct Zona zonas[], int totalZonas, int soloUnaZona) {
    int inicio = 0, fin = totalZonas;

    if (soloUnaZona) {
        printf("Seleccione zona (0 a %d): ", totalZonas - 1);
        scanf("%d", &inicio);
        fin = inicio + 1;
    }

    for (int i = inicio; i < fin; i++) {
        int hayProblema = 0;
        for (int j = 0; j < 4; j++) {
            if (zonas[i].prediccion[j] > 25.0) {
                hayProblema = 1;
                break;
            }
        }
        if (hayProblema) {
            printf("Recomendaciones para zona %s:\n", zonas[i].nombre);
            printf("- Reducir trafico vehicular\n");
            printf("- Suspender actividades al aire libre\n");
            printf("- Restringir emisiones industriales\n\n");
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

void editarContaminacion(struct Zona zonas[], int totalZonas) {
    int zonaIndex, contaminante;
    printf("Seleccione zona (0-%d): ", totalZonas - 1);
    scanf("%d", &zonaIndex);

    if (zonaIndex < 0 || zonaIndex >= totalZonas) {
        printf("Zona invalida.\n");
        return;
    }

    printf("Seleccione contaminante a editar:\n");
    printf("1. PM2.5\n2. CO2\n3. NO2\n4. SO2\nOpcion: ");
    scanf("%d", &contaminante);

    if (contaminante < 1 || contaminante > 4) {
        printf("Opcion invalida.\n");
        return;
    }

    printf("Valor actual: %.2f\n", zonas[zonaIndex].actual[contaminante - 1]);
    printf("Ingrese nuevo valor: ");
    float nuevoValor;
    scanf("%f", &nuevoValor);

    zonas[zonaIndex].actual[contaminante - 1] = nuevoValor;
    zonas[zonaIndex].historico[contaminante - 1][0] = nuevoValor;
    printf("Valor actualizado correctamente.\n");
}