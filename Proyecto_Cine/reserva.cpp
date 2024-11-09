#include "reserva.h"
#include "ui_reserva.h"

reserva::reserva(QString fecha, int cantasientos, Cliente *cliente, Horarios *horario, pagos *pago, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::reserva)
{
    ui->setupUi(this);
}

reserva::~reserva()
{
    delete ui;
}
