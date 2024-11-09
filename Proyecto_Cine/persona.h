#ifndef PERSONA_H
#define PERSONA_H

#include "string"

class Persona
{
    string Nombre;
    string Apellido;
    int Dni;
    int Edad;
    int Telefono;
public:
    Persona(string nombre, string apellido, int dni, int edad, int telefono);
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
