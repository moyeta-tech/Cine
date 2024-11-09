#ifndef PERSONA_H
#define PERSONA_H

#include "string"
using namespace std;

class Persona
{
    string Nombre;
    string Apellido;
    int Dni;
    int Edad;
    int Telefono;
public:
    Persona(); // CONSTRUCTOR POR DEFECTO
    Persona(string nombre, string apellido, int dni, int edad, int telefono); // CONSTRUCTOR QUE USA PARAMETROS
    string getNombre();
    void setNombre(string nombre);
    string getApellido();
    void setApellido(string apellido);
    int getDni();
    void setDni(int dni);
    int getEdad();
    void setEdad(int edad);
    int getTelefono();
    void setTelefono(int telefono);

};

#endif // PERSONA_H
