#include "cine.h"
#include "ui_cine.h"

Cine::Cine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cine)
{
    ui->setupUi(this);
}

Cine::~Cine()
{
    delete ui;
}
