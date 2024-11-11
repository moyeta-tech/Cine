#include "clientes.h"
#include "ui_clientes.h"

Clientes::Clientes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Clientes)
{
    ui->setupUi(this);

    this->setWindowTitle("Formulario de clientes");

}

Clientes::~Clientes()
{
    delete ui;
}

// GET Y SET DE IDCLIENTE

int Clientes::getIDcliente(){
    return idCliente;
}
void Clientes::setIDcliente(int idcliente){
    idCliente = idcliente;
}

// GET DE HISTORIAL
/*
std::vector<QString> Clientes::getHistorial(){
    return Historial;
}

void Clientes::agregarHistorial(reserva *Reserva){
    this->Reserva = Reserva;
}
*/

/*
void Clientes::mostrarHistorial(){
    cout << "Historial: " << Historial << endl;
}
*/
