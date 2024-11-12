#include "asientos.h"
#include "ui_asientos.h"

#include "pago.h"

Asientos::Asientos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Asientos)
{
    ui->setupUi(this);

    this->setWindowTitle("Seleccion de asiento");

    //Conectamos el boton continuar para llegar a la ventana de pago
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Asientos::continuarPago);
}

Asientos::~Asientos()
{
    delete ui;
}

// GET Y SET DE NUMERO

int Asientos::getNumero()
{
    return Numero;
}
void Asientos::setNumero(int numero)
{
    Numero = numero;
}

// GET Y SET DE FILA

QString Asientos::getFila()
{
    return Fila;
}


void Asientos::setFila(QString fila)
{
    Fila = fila;
}

// En asientos.cpp

void Asientos::continuarPago()
{
    QString metodo = "Tarjeta"; // Puedes obtener este valor de alguna propiedad de Asientos
    float monto = 100.0f; // Obtener monto de alguna propiedad de Asientos
    QString fecha = "2024-11-11"; // Obtener fecha de alguna propiedad de Asientos
    Pago dialog(metodo, monto, fecha, this); // Pasa los parámetros correctamente
    dialog.exec();
}

