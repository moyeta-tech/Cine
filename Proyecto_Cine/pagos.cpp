
#include "pagos.h"
#include "ui_pagos.h"

pagos::pagos(QString metodo, float monto, QString fecha, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pagos)
{
    ui->setupUi(this);
}

pagos::~pagos()
{
    delete ui;
}

// GET Y SET DE METODO

QString pagos::getMetodo(){
    return Metodo;
}

void pagos::setMetodo(QString metodo){
    Metodo = metodo;
}

// GET Y SET DE MONTO

float pagos::getMonto(){
    return Monto;
}

void pagos::setMonto(float monto){
    Monto = monto;
}

// GET Y SET DE FECHA

QString pagos::getFecha(){
    return Fecha;
}

void pagos::setFecha(QString fecha){
    Fecha = fecha;
}





