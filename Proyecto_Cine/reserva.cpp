#include "reserva.h"
#include "ui_reserva.h"

reserva::reserva(QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, pagos *pago, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::reserva)
{
    ui->setupUi(this);
}

reserva::~reserva()
{
    delete ui;
}

// GET Y SET DE FECHA

QString reserva::getFecha(){
    return Fecha;
}

void reserva::setFecha(QString fecha){
    Fecha = fecha;
}

// GET Y SET DE CANTASIENTOS

int reserva::getcantAsientos(){
    return cantAsientos;
}

void reserva::setcantAsientos(int cantasientos){
    cantAsientos = cantasientos;
}

// GET Y SET DE CLIENTE

Clientes *reserva::getCliente(){
    return cliente;
}

void reserva::setCliente(Clientes *cliente){
    this->cliente = cliente;
}

// GET Y SET DE HORARIO

Horarios *reserva::getHorario(){
    return horario;
}

void reserva::setHorario(Horarios *horario){
    this->horario = horario;
}

// GET Y SET DE PAGO

pagos *reserva::getPago(){
    return pago;
}

void reserva::setPago(pagos *pago){
    this->pago = pago;
}
