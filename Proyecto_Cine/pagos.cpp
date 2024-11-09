#include "pagos.h"
#include "ui_pagos.h"

pagos::pagos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pagos)
{
    ui->setupUi(this);
}

pagos::~pagos()
{
    delete ui;
}
