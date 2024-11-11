#include "asientos.h"
#include "ui_asientos.h"

asientos::asientos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::asientos)
{
    ui->setupUi(this);
}

asientos::~asientos()
{
    delete ui;
}

// GET Y SET DE NUMERO

int asientos::getNumero(){
    return Numero;
}
void asientos::setNumero(int numero){
    Numero = numero;
}

// GET Y SET DE FILA

QString asientos::getFila(){
    return Fila;
}


void asientos::setFila(QString fila){
    Fila = fila;
}
