struct Clima {
    float temperatura;
    float humedad;
    float viento;
};

struct Zona {
    char nombre[50];
    float historico[4][30]; // 4 contaminantes
    float actual[4];
    float prediccion[4];
};

// Prototipos de funciones
int menu();
void inicializarZonas(struct Zona zonas[], int *totalZonas);
void registrarContaminacionPorZona(struct Zona zonas[], int totalZonas);
void registrarContaminacionPorContaminante(struct Zona zonas[], int totalZonas);
void calcularPromedios(struct Zona zonas[], int totalZonas, int soloUnaZona);
void predecirContaminacion(struct Zona zonas[], int totalZonas, struct Clima clima, int soloUnaZona);
void generarAlertas(struct Zona zonas[], int totalZonas, int soloUnaZona);
void generarRecomendaciones(struct Zona zonas[], int totalZonas, int soloUnaZona);
void editarContaminacion(struct Zona zonas[], int totalZonas);  
void exportarDatos(struct Zona zonas[], int totalZonas);
void predecirPorZona(struct Zona zonas[], int totalZonas, struct Clima clima);
void predecirPorContaminante(struct Zona zonas[], int totalZonas, struct Clima clima);
