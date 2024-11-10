#include "persona.h"
#ifndef CLIENTE_H
#define CLIENTE_H
#include "vector"

using namespace std;

class Cliente : public Persona
{
    int idCliente;
    std::vector<string> historial;
public:
    Cliente (string nombre, string apellido, int dni, int edad, int teléfono, int idCliente);
    int getIDcliente();
    void setIDcliente(int idcliente);
    void agregarHistorial(string reserva);
    // void getHistorial(historial);
    void mostrarHistorial();
};

#endif // CLIENTE_H
