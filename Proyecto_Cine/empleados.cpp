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
