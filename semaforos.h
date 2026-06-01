#ifndef SEMAFOROS_H_INCLUDED
#define SEMAFOROS_H_INCLUDED
#include <mutex>
#include <condition_variable>
using namespace std;

struct Semaforo {
    int contador;
    mutex mtx;
    condition_variable cv;
};

void init(Semaforo& s, int n);
void wait(Semaforo& s);
void signal(Semaforo& s);

#endif // SEMAFORO_H_INCLUDED
