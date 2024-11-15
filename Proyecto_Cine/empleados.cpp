#include "empleados.h"
#include "ui_empleados.h"

Empleados::Empleados(std::vector<Empleados *> &vectorEmpleadosRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Empleados)
    , vectorEmpleados(vectorEmpleadosRef)
{

    //Empleado::Empleado(string nombre, string apellido, int dni, int edad, int telefono, int idempleado) {}

    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Formulario de empleados");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();
}

Empleados::~Empleados()
{
    delete ui;
}

// GET Y SET DE IDEMPLEADO

int Empleados::getIDempleado()
{
    return idEmpleado;
}

void Empleados::setIDempleado(int idempleado)
{
    idEmpleado = idempleado;
}

// GET Y SET DE NOMBRE

QString Empleados::getNombre(){
    return Nombre;
}

void Empleados::setNombre(QString nombre){
    Nombre = nombre;
}

// GET Y SET DE APELLIDO

QString Empleados::getApellido(){
    return Apellido;
}

void Empleados::setApellido(QString apellido){
    Apellido = apellido;
}

// GET Y SET DE DNI

int Empleados::getDni(){
    return Dni;
}

void Empleados::setDni(int dni){
    Dni = dni;
}

// GET Y SET DE EDAD

int Empleados::getEdad(){
    return Edad;
}

void Empleados::setEdad(int edad){
    Edad = edad;
}

// GET Y SET DE TELEFONO

int Empleados::getTelefono(){
    return Telefono;
}

void Empleados::setTelefono(int telefono){
    Telefono = telefono;
}

// GET Y SET DE PUESTO

QString Empleados::getPuesto(){
    return Puesto;
}

void Empleados::setPuesto(QString puesto){
    Puesto = puesto;
}

// HOJA DE ESTILOS
void Empleados::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

void Empleados::on_buttonBox_accepted()
{
    Empleados *empleado = new Empleados(vectorEmpleados, this);

    empleado->setIDempleado(ui->lineEdit->text().toInt());
    empleado->setNombre(ui->lineEdit_2->text());
    empleado->setApellido(ui->lineEdit_3->text());
    empleado->setDni(ui->lineEdit_4->text().toInt());
    empleado->setEdad(ui->spinBox->value());
    empleado->setTelefono(ui->lineEdit_5->text().toInt());
    empleado->setPuesto(ui->lineEdit_6->text());

    vectorEmpleados.push_back(empleado);

    emit empleadoAgregado(empleado->getIDempleado(), empleado->getNombre(),
                          empleado->getApellido(), empleado->getDni(),
                          empleado->getEdad(), empleado->getTelefono(),
                          empleado->getPuesto());
}

