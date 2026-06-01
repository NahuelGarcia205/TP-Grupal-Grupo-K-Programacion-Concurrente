#include "procesamiento.h"
#include "globales.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

void productor(int idProductor, int cantidadPaquetes)
{
    for(int i =0;i<cantidadPaquetes;i++)
    {
        Paquete p;
        {
            lock_guard<mutex> lockId(mtxId);
            p.id = idGlobal++;
        }

        {
            lock_guard<mutex> lockRand(mtxRand);
            p.prioridad = rand() % 2;
        }


        p.prioridadOriginal = p.prioridad;
        p.tiempoIngreso = time(0);

        this_thread::sleep_for(chrono::milliseconds(90)); //90
        {
            lock_guard<mutex> lock(mtxColaEspera);
            colaEspera.push(p);
            lock_guard<mutex> lockC(mtxConsola);
            cout << "[PRODUCTOR "<< idProductor<< "] produjo paquete "<< p.id<< " | prioridad: "<< p.prioridad<< endl;
        }
        signal(paquetesDisponibles);
    }
}

void consumidor(int idConsumidor)
{
    while(true)
    {
        wait(paquetesDisponibles);
        Paquete p;
        {
            lock_guard<mutex> lock(mtxColaEspera);
            if(colaEspera.empty())
            {
                if(finProduccion)
                {
                    break;
                }
                continue;
            }
            p = colaEspera.top();
            colaEspera.pop();
        }
        long tiempoActual = time(0);

        if(p.prioridad == 0 && (tiempoActual - p.tiempoIngreso)>=6)
        {
            p.prioridad = 1;
            lock_guard<mutex> lockC(mtxConsola);
            cout<<"[AGING] paquete "<< p.id<<" subio a prioridad ALTA"<<endl;
        }

        wait(espaciosDisponibles);
        {
            lock_guard<mutex> lock(mtxAsignacion);

            this_thread::sleep_for(chrono::milliseconds(420)); //420


            {
                lock_guard<mutex> lockCola(mtxColaProcesamiento);
                colaProcesamiento.push(p);
                //cout << "[PROCESANDO] tamanio actual: "<< colaProcesamiento.size() << endl; //solo para 8 paquetes
            }
        }

        {
            lock_guard<mutex> lockConsola(mtxConsola);
            cout << "--- [CONSUMIDOR "<< idConsumidor<< "] procesa paquete "<< p.id<< " | prioridad: "<< p.prioridad<< endl;
        }

        this_thread::sleep_for(chrono::milliseconds(550)); //550

        {
            lock_guard<mutex> lockL(mtxLiberacion);
            this_thread::sleep_for(chrono::milliseconds(270)); // 270

            {
                lock_guard<mutex> lockPros(mtxColaProcesamiento);
                if(!colaProcesamiento.empty())
                {
                    long tiempoFinal = time(0);
                    double tiempoEspera = tiempoFinal - p.tiempoIngreso;
                    lock_guard<mutex> lockMet(mtxMetricas);
                    if(p.prioridadOriginal == 1)
                    {
                        totalAlta++;
                        esperaAlta += tiempoEspera;
                    }
                    else
                    {
                        totalBaja++;
                        esperaBaja += tiempoEspera;
                    }
                colaProcesamiento.pop();
                lock_guard<mutex> lock2(mtxConsola);
                cout<<"[CONSUMIDOR "<<idConsumidor<<"] finalizo paquete "<<p.id<<endl;
                }
            }
        }

        signal(espaciosDisponibles);

    }
    lock_guard<mutex> lockC(mtxConsola);
    cout<<"[CONSUMIDOR "<<idConsumidor<<"] termino ejecucion."<<endl;
}
