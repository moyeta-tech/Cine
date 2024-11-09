#include "precios.h"
#include "ui_precios.h"

precios::precios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::precios)
{
    ui->setupUi(this);
}

precios::~precios()
{
    delete ui;
}
