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
