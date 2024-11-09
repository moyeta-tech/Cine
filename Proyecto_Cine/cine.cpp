#include "cine.h"
#include "ui_cine.h"

Cine::Cine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cine)
{

     qDebug() << "Iniciando Cine";
    ui->setupUi(this);
     qDebug() << "Interfaz de usuario cargada";

}

Cine::~Cine()
{
    qDebug() << "Destruyendo Cine..";
    delete ui;
}


QString Cine::getNombre(){
    return Nombre;
}

void Cine::setNombre(QString nombre){

}

QString Cine::getUbicacion(){
    return Ubicacion;
}

void Cine::setUbicacion(QString Ubicacion){

}

