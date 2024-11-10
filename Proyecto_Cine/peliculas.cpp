#include "peliculas.h"
#include "ui_peliculas.h"

Peliculas::Peliculas(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas)
{
    ui->setupUi(this);

    //Titulo de la ventana
    this->setWindowTitle("Peliculas");
}

Peliculas::~Peliculas()
{
    delete ui;
}
