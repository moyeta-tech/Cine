#include "reserva.h"
#include "ui_reserva.h"

reserva::reserva(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::reserva)
{
    ui->setupUi(this);
}

reserva::~reserva()
{
    delete ui;
}
