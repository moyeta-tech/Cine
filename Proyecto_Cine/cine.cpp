#include "cine.h"
#include "ui_cine.h"

#include "peliculas.h"
#include "clientes.h"
#include "empleados.h"


Cine::Cine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cine)
{

    qDebug() << "Iniciando Cine";
    ui->setupUi(this);
    qDebug() << "Interfaz de usuario cargada";

    //Titulo de la ventana
    this->setWindowTitle("Inicio");

    //Boton de prueba para agregar pelicula
    connect(ui->actionRegistro_peliculas, &QAction::triggered, this, &Cine::agregarPelicula);

    connect (ui->actionRegistrar_clientes, &QAction::triggered, this, &Cine::agregarClientes);


    connect (ui->actionRegistrar_personal, &QAction::triggered, this, &Cine::agregarEmpleados);

}

Cine::~Cine()
{
    qDebug() << "Destruyendo Cine..";
    delete ui;
}


QString Cine::getNombre(){
    return Nombre;
}

/*
 void Cine::setNombre(QString nombre){

}

QString Cine::getUbicacion(){
    return Ubicacion;
}

void Cine::setUbicacion(QString Ubicacion){

}
*/

void Cine::agregarPelicula()
{
    Peliculas dialog("Nueva Película", 120, "Acción", "PG-13", "Sinopsis de la película", this);
    dialog.exec();
}

void Cine::agregarClientes()
{
    Clientes dialog(this);
    dialog.exec();

}

void Cine::agregarEmpleados()
{
    Empleados dialog(this);
    dialog.exec();
}
