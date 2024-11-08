#include "pelicula.h"
#include "ui_pelicula.h"

Pelicula::Pelicula(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pelicula)
{
    ui->setupUi(this);
}

Pelicula::~Pelicula()
{
    delete ui;
}
