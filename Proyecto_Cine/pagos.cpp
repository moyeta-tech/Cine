#include "pagos.h"
#include "ui_pagos.h"

pagos::pagos(QString metodo, float monto, QString fecha, QWidget *parent = nullptr)
    : QWidget(parent)
    , ui(new Ui::pagos)
{
    ui->setupUi(this);
}

pagos::~pagos()
{
    delete ui;
}
