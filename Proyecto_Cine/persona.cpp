#include "persona.h"

Persona::Persona(){

}

Persona::Persona(string nombre, string apellido, int dni, int edad, int telefono) {}

// GET Y SET DE NOMBRE

string Persona::getNombre(){
    return Nombre;
}

void Persona::setNombre(string nombre){
    Nombre = nombre;
}

// GET Y SET DE APELLIDO

string Persona::getApellido(){
    return Apellido;
}

void Persona::setApellido(string apellido){
    Apellido = apellido;
}

// GET Y SET DE DNI

int Persona::getDni(){
    return Dni;
}

void Persona::setDni(int dni){
    Dni = dni;
}

// GET Y SET DE EDAD

int Persona::getEdad(){
    return Edad;
}

void Persona::setEdad(int edad){
    Edad = edad;
}

// GET Y SET DE TELEFONO

int Persona::getTelefono(){
    return Telefono;
}

void Persona::setTelefono(int telefono){
    Telefono = telefono;
}
