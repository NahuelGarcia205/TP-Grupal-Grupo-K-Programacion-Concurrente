#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include "procesamiento.h"
#include "globales.h"
#include "semaforos.h"

using namespace std;



int main()
{
    // reinicio de semilla
    srand(time(0));

    init(espaciosDisponibles, 5);
    init(paquetesDisponibles, 0);

    vector<thread> productores;
    vector<thread> consumidores;

    //cree los hilos, agreguen las variables globalas o los semaforos

    for(int i=1;i<=CANT_PRODUCTORES;i++)
    {
        int paquetesAProducir = cantidadBase;
        if(i <= resto)
        {
            paquetesAProducir++;
        }
        productores.emplace_back(productor, i, paquetesAProducir);
    }

    for(int i=1;i<=CANT_CONSUMIDORES;i++)
    {
        consumidores.emplace_back(consumidor, i);
    }

    for(auto& t : productores)
    {
        t.join();
    }

    finProduccion = true;

    cout << "\n=== PRODUCCION FINALIZADA ===\n" << endl;

    for(int i =0;i<CANT_CONSUMIDORES;i++)
    {
        signal(paquetesDisponibles);
    }

    for(auto& t : consumidores)
    {
        t.join();
    }

    cout<<"\n===== METRICAS =====\n";
    cout<<"Paquetes producidos: "<<(totalAlta + totalBaja)<<endl;
    cout<<"Paquetes alta prioridad: "<<totalAlta<<endl;
    cout<<"Paquetes baja prioridad: "<<totalBaja<<endl;

    if(totalAlta>0)
    {
        cout<<"Espera promedio alta: "<<(esperaAlta/totalAlta)<<" segundos"<<endl;
    }

    if(totalBaja>0)
    {
        cout<<"Espera promedio baja: "<<(esperaBaja/totalBaja)<<" segundos"<< endl;
    }

    cout<<"\n=== SISTEMA FINALIZADO ==="<<endl;

    return 0;
}
