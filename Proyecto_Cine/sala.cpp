#include "Sala.h"

    // Constructor
    sala::sala(int num, int numAsientos)
    : numero(num), asientos(numAsientos, false) {
}
    // Métodos
    int sala::getNumero() const {
        return numero;
    }

    bool sala::checkAsiento(int asiento) const{


    }
