#include "horarios.h"
#include "ui_horarios.h"

Horarios::Horarios(QString hora, QString dia, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Horarios)
{
    ui->setupUi(this);
}

Horarios::~Horarios()
{
    delete ui;
}

// GET Y SET DE HORA
QString Horarios::getHora(){
    return Hora;
}

void Horarios::setHora(QString hora){
    Hora = hora;
}

// GET Y SET DE DIA

QString Horarios::getDia(){
    return Dia;
}

void Horarios::setDia(QString dia){
    Dia = dia;
}
