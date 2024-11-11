#include "empleados.h"
#include "ui_empleados.h"

Empleados::Empleados(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Empleados)
{

    //Empleado::Empleado(string nombre, string apellido, int dni, int edad, int telefono, int idempleado) {}

    ui->setupUi(this);

    this->setWindowTitle("Formulario de empleados");
}

Empleados::~Empleados()
{
    delete ui;
}

// GET Y SET DE IDEMPLEADO

int Empleados::getIDempleado(){
    return idEmpleado;
}

void Empleados::setIDempleado(int idempleado){
    idEmpleado = idempleado;
}

// GET Y SET DE PUESTO

QString Empleados::getPuesto(){
    return Puesto;
}

void Empleados::setPuesto(QString puesto){
    Puesto = puesto;
}
