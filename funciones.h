struct Zona {
    char nombre[50];
    float actual;
    float prediccion;
    float historico[30]; // Últimos 30 días
};

struct Clima {
    float temperatura;
    float humedad;
    float viento;
};

// Prototipos de funciones
void inicializarZonas(struct Zona zonas[], int *totalZonas);
void registrarContaminacion(struct Zona zonas[], int totalZonas);
void calcularPromedios(struct Zona zonas[], int totalZonas);
void predecirContaminacion(struct Zona zonas[], int totalZonas, struct Clima clima);
void generarAlertas(struct Zona zonas[], int totalZonas);
void generarRecomendaciones(struct Zona zonas[], int totalZonas);
void exportarDatos(struct Zona zonas[], int totalZonas);
