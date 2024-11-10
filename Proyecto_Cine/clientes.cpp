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
