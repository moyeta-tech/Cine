#include "pago.h"
#include "ui_pago.h"

Pago::Pago(QString metodo, float monto, QString fecha, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Pago)
{
    ui->setupUi(this);
}

Pago::~Pago()
{
    delete ui;
}

// GET Y SET DE METODO

QString Pago::getMetodo(){
    return Metodo;
}

void Pago::setMetodo(QString metodo){
    Metodo = metodo;
}

// GET Y SET DE MONTO

float Pago::getMonto(){
    return Monto;
}

void Pago::setMonto(float monto){
    Monto = monto;
}

// GET Y SET DE FECHA

QString Pago::getFecha(){
    return Fecha;
}

void Pago::setFecha(QString fecha){
    Fecha = fecha;
}




