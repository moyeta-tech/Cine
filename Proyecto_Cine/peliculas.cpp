#include "peliculas.h"
#include "ui_peliculas.h"

peliculas::peliculas(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::peliculas)
{
    ui->setupUi(this);
}

peliculas::~peliculas()
{
    delete ui;
}
