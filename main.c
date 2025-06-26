#include <stdio.h>
#include "funciones.h"

int menu() {
    int opc;
    printf("\n--- SIGPCA: Sistema Integral de Gestion y Prediccion de Contaminacion del Aire ---\n");
    printf("1. Inicializar zonas\n");
    printf("2. Registrar niveles actuales de contaminacion\n");
    printf("3. Calcular promedios historicos\n");
    printf("4. Predecir niveles de contaminacion\n");
    printf("5. Generar alertas preventivas\n");
    printf("6. Generar recomendaciones\n");
    printf("7. Exportar datos del sistema\n");
    printf("8. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opc);
    return opc;
}

int main() {
    struct Zona zonas[10];
    struct Clima clima;
    int totalZonas = 0;
    int opcion;

    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                inicializarZonas(zonas, &totalZonas);
                printf("Zonas inicializadas correctamente.\n");
                break;
            case 2:
                if (totalZonas > 0) {
                    registrarContaminacion(zonas, totalZonas);
                } else {
                    printf("Primero debe inicializar las zonas.\n");
                }
                break;
            case 3:
                if (totalZonas > 0) {
                    calcularPromedios(zonas, totalZonas);
                } else {
                    printf("No hay datos disponibles.\n");
                }
                break;
            case 4:
                if (totalZonas > 0) {
                    printf("Ingrese datos climaticos actuales:\n");
                    printf("Temperatura (°C): ");
                    scanf("%f", &clima.temperatura);
                    printf("Humedad (%%): ");
                    scanf("%f", &clima.humedad);
                    printf("Velocidad del viento (km/h): ");
                    scanf("%f", &clima.viento);
                    predecirContaminacion(zonas, totalZonas, clima);
                } else {
                    printf("Debe ingresar datos primero.\n");
                }
                break;
            case 5:
                if (totalZonas > 0) {
                    generarAlertas(zonas, totalZonas);
                } else {
                    printf("No hay datos para analizar.\n");
                }
                break;
            case 6:
                if (totalZonas > 0) {
                    generarRecomendaciones(zonas, totalZonas);
                } else {
                    printf("No hay predicciones para generar recomendaciones.\n");
                }
                break;
            case 7:
                if (totalZonas > 0) {
                    exportarDatos(zonas, totalZonas);
                } else {
                    printf("No hay datos para exportar.\n");
                }
                break;
            case 8:
                printf("Saliendo del sistema SIGPCA...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 8);

    return 0;
}
