#include <stdio.h>
#include "funciones.h"


int main() {
    struct Zona zonas[5]; // 5 zonas
    struct Clima clima;
    clima.temperatura = 25.0;
    clima.humedad = 65.0;
    clima.viento = 4.0;

    int totalZonas = 0;
    int opcion;

    const char *contaminantes[] = {"PM2.5", "CO2", "NO2", "SO2"};

    do {
        opcion = menu();

        switch(opcion) {
            case 1:
                inicializarZonas(zonas, &totalZonas);
                printf("Zonas inicializadas correctamente.\n");
                break;

            case 2:
                for (int i = 0; i < totalZonas; i++) {
                    printf("Zona: %s\n", zonas[i].nombre);
                    for (int j = 0; j < 4; j++) {
                        printf("Ingrese valor para %s: ", contaminantes[j]);
                        scanf("%f", &zonas[i].actual[j]);
                        for (int k = 29; k > 0; k--) {
                            zonas[i].historico[j][k] = zonas[i].historico[j][k - 1];
                        }
                        zonas[i].historico[j][0] = zonas[i].actual[j];
                    }
                }
                break;

            case 3:
                registrarContaminacionPorZona(zonas, totalZonas);
                break;

            case 4: {
                int op;
                printf("1. Calcular por zona\n2. Calcular total\nOpcion: ");
                scanf("%d", &op);
                calcularPromedios(zonas, totalZonas, op == 1);
                break;
            }

            case 5: {
                int op;
                printf("1. Predecir por zona\n2. Predecir total\nOpcion: ");
                scanf("%d", &op);
                predecirContaminacion(zonas, totalZonas, clima, op == 1);
                break;
            }

            case 6: {
                int op;
                printf("1. Generar alertas por zona\n2. Generar alertas total\nOpcion: ");
                scanf("%d", &op);
                generarAlertas(zonas, totalZonas, op == 1);
                break;
            }

            case 7: {
                int op;
                printf("1. Recomendaciones por zona\n2. Recomendaciones total\nOpcion: ");
                scanf("%d", &op);
                generarRecomendaciones(zonas, totalZonas, op == 1);
                break;
            }

            case 8:
                editarContaminacion(zonas, totalZonas);
                break;

            case 9:
                exportarDatos(zonas, totalZonas);
                break;

            case 10:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while(opcion != 10);

    return 0;
}