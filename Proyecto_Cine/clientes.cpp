#include "clientes.h"
#include "ui_clientes.h"

Clientes::Clientes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Clientes)
{
    ui->setupUi(this);

    this->setWindowTitle("Formulario de clientes");

    initstylesheet();
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

void Clientes::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
