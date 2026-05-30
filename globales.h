#ifndef GLOBALES_H_INCLUDED
#define GLOBALES_H_INCLUDED
#include <queue>
#include <vector>
#include <mutex>
#include "paquete.h"
#include "semaforo.h"
#include "prioridades.h"

using namespace std;

extern priority_queue<Paquete,vector<Paquete>,ComparadorPaquetes> colaEspera;
extern queue<Paquete> colaProcesamiento;

// MUTEX
extern mutex mtxColaEspera;
extern mutex mtxColaProcesamiento;
extern mutex mtxId;
extern mutex mtxConsola;
extern mutex mtxMetricas;
extern mutex mtxLiberacion;
extern mutex mtxAsignacion;

// SEMAFOROS
extern Semaforo espaciosDisponibles;
extern Semaforo paquetesDisponibles;

// VARIABLES GLOBALES
extern int idGlobal;
extern bool finProduccion;
extern int paquetes;
extern int CANT_PRODUCTORES;
extern int CANT_CONSUMIDORES;
extern int cantidadBase;
extern int resto;

//METRICAS
extern int totalAlta;
extern int totalBaja;
extern double esperaAlta;
extern double esperaBaja;

#endif
