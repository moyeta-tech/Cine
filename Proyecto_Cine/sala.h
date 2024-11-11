#ifndef SALA_H
#define SALA_H

#include <vector>
#include "string"

using namespace std;


class sala {

private:
    int NumSala;
    int Capacidad;

public:

    //Constructor

    sala(int numsala, int capacidad);


    //Metodos
    int getNumSala();
    void setNumSala (int numsala);
    int getCapacidad();
    void setCapacidad (int capacidad);

};

#endif // SALA_H
