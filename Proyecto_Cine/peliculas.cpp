#include "peliculas.h"
#include "ui_peliculas.h"

peliculas::peliculas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::peliculas)
{
    ui->setupUi(this);
}

peliculas::~peliculas()
{
    delete ui;
}
