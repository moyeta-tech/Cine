#include "empleados.h"
#include "ui_empleados.h"

Empleados::Empleados(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Empleados)
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

// GET Y SET DE PUESTO

QString Empleados::getPuesto()
{
    return Puesto;
}

void Empleados::setPuesto(QString puesto)
{
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
