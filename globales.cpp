#include "globales.h"

using namespace std;

priority_queue<Paquete,vector<Paquete>,ComparadorPaquetes> colaEspera;
queue<Paquete> colaProcesamiento;

// MUTEX
mutex mtxColaEspera;
mutex mtxColaProcesamiento;
mutex mtxId;
mutex mtxConsola;
mutex mtxMetricas;
mutex mtxLiberacion;
mutex mtxAsignacion;

// SEMAFOROS
Semaforo espaciosDisponibles;
Semaforo paquetesDisponibles;

// VARIABLES GLOBALES
int idGlobal = 1;
bool finProduccion = false;
int paquetes = 20;
int CANT_PRODUCTORES = 3;
int CANT_CONSUMIDORES = 2;
int cantidadBase = paquetes / CANT_PRODUCTORES;
int resto = paquetes % CANT_PRODUCTORES;

//METRICAS
int totalAlta = 0;
int totalBaja = 0;
double esperaAlta = 0;
double esperaBaja = 0;
