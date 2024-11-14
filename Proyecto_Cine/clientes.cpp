#include "clientes.h"
#include "ui_clientes.h"

Clientes::Clientes(std::vector<Clientes *> &vectorClientesRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Clientes)
    , vectorClientes(vectorClientesRef)
{
    ui->setupUi(this);

    //Establecemos el titul ode la ventana
    this->setWindowTitle("Formulario de clientes");

    //Llamamos al slot para cargar el stylesheet
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

// GET Y SET DE NOMBRE

string Clientes::getNombre(){
    return Nombre;
}

void Clientes::setNombre(string nombre){
    Nombre = nombre;
}

// GET Y SET DE APELLIDO

string Clientes::getApellido(){
    return Apellido;
}

void Clientes::setApellido(string apellido){
    Apellido = apellido;
}

// GET Y SET DE DNI

int Clientes::getDni(){
    return Dni;
}

void Clientes::setDni(int dni){
    Dni = dni;
}

// GET Y SET DE EDAD

int Clientes::getEdad(){
    return Edad;
}

void Clientes::setEdad(int edad){
    Edad = edad;
}

// GET Y SET DE TELEFONO

int Clientes::getTelefono(){
    return Telefono;
}

void Clientes::setTelefono(int telefono){
    Telefono = telefono;
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



void Clientes::on_buttonBox_accepted()
{
    Clientes *cliente = new Clientes(vectorClientes, this);

    cliente->setIDcliente(ui->lineEdit->text().toInt());
    cliente->setNombre(ui->lineEdit_2->text().toStdString());
    cliente->setApellido(ui->lineEdit_3->text().toStdString());
    cliente->setDni(ui->lineEdit_4->text().toInt());
    cliente->setEdad(ui->spinBox->value());
    cliente->setTelefono(ui->lineEdit_5->text().toInt());

    vectorClientes.push_back(cliente); // INTRODUCIMOS LOS DATOS

     // Usar qDebug() para verificar si los datos se están ingresando

    for(Clientes *c : vectorClientes)
    {
        qDebug() << "IdCliente: " << c->getIDcliente();
        qDebug() << "Nombre: " << c->getNombre();
        qDebug() << "Apellido: " << c->getApellido();
        qDebug() << "Dni: " << c->getDni();
        qDebug() << "Edad: " << c->getEdad();
        qDebug() << "Telefono: " << c->getTelefono();

    }

    emit clienteAgregado(cliente->getIDcliente(), cliente->getNombre(),
                         cliente->getApellido(), cliente->getDni(),
                         cliente->getEdad(), cliente->getTelefono());
}
