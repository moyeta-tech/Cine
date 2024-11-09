#ifndef SALA_H
#define SALA_H

#include <vector>


class sala {

private:
    int numero;
    std::vector<bool> asientos;
public:

    //Constructor

    sala(int num, int numAsientos);


    //Metodos

    int getNumero() const;
    bool checkAsiento(int asiento) const;
    void ocuparAsiento(int asiento);
    void liberarAsiento(int asiento);
    void mostrarEstado() const;

};

#endif // SALA_H
