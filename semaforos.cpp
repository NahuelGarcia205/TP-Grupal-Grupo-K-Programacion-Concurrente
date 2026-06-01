#include "semaforos.h"
using namespace std;

void init(Semaforo& s, int n) {
    s.contador = n;
}

void wait(Semaforo& s) {
    unique_lock<mutex> lock(s.mtx);

    while (s.contador == 0) {
        s.cv.wait(lock);
    }

    s.contador--;
}

void signal(Semaforo& s) {
    unique_lock<mutex> lock(s.mtx);

    s.contador++;
    s.cv.notify_one();
}
