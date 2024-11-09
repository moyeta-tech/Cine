#include "persona.h"
#ifndef EMPLEADO_H
#define EMPLEADO_H

using namespace std;

class Empleado : public Persona
{
    int idEmpleado;
    string Puesto;
public:
    Empleado(string nombre, string apellido, int dni, int edad, int telefono, int idempleado);
    int getIDempleado();
    void setIDempleado(int idempleado);
    string getPuesto();
    void setPuesto(string puesto);




};

#endif // EMPLEADO_H
