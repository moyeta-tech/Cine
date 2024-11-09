#include "persona.h"
#ifndef EMPLEADO_H
#define EMPLEADO_H
#include "vector"

class Empleado : public Persona
{
    int idCliente;
    std::vector<string> historial;
public:
    Empleado(string nombre, string apellido, int dni, int edad, int telefono, int idcliente);
    int getIDcliente();
    void setIDcliente(int idcliente);
    void agregarHistorial(string reserva);




};

#endif // EMPLEADO_H
