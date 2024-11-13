#include "peliculas.h"
#include "ui_peliculas.h"

Peliculas::Peliculas(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas)
{
    ui->setupUi(this);

    //Titulo de la ventana
    this->setWindowTitle("Peliculas");

    initstylesheet();
}

Peliculas::~Peliculas()
{
    delete ui;
}

// GET Y SET DE TITULO

QString Peliculas::getTitulo(){
    return Titulo;
}

void Peliculas::setTitulo(QString titulo){
    Titulo = titulo;
}

// GET Y SET DE DURACION

int Peliculas::getDuracion(){
    return Duracion;
}

void Peliculas::setDuracion(int duracion){
    Duracion = duracion;
}

// GET Y SET DE GENERO

QString Peliculas::getGenero(){
    return Genero;
}

void Peliculas::setGenero(QString genero){
    Genero = genero;
}

// GET Y SET DE CLASIFICACION

QString Peliculas::getClasificacion(){
    return Clasificacion;
}

void Peliculas::setClasificacion(QString clasificacion){
    Clasificacion = clasificacion;
}

// GET Y SET DE SINOPSIS

QString Peliculas::getSinopsis(){
    return Sinopsis;
}

void Peliculas::setSinopsis(QString sinopsis){
    Sinopsis = sinopsis;
}

void Peliculas::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

