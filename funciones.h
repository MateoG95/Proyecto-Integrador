struct Zona {
    char nombre[30];
    float historico[30];  // Niveles de contaminacion en los ultimos 30 dias
    float actual;         // Nivel actual
    float prediccion;     // Prediccion para las siguientes 24 horas
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
