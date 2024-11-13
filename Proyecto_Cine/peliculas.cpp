#include "peliculas.h"
#include "ui_peliculas.h"

Peliculas::Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas),
    vectorPelicula(vectorPeliculaRef)
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


void Peliculas::on_pushButton_2_clicked()
{
    Peliculas *pelicula = new Peliculas(vectorPelicula, this);

    pelicula->setTitulo(ui->lineEdit_2->text());
    pelicula->setDuracion(ui->spinBox->value());
    pelicula->setGenero(ui->lineEdit_4->text());
    pelicula->setClasificacion(ui->lineEdit_5->text());
    pelicula->setSinopsis(ui->textEdit->toPlainText());

    vectorPelicula.push_back(pelicula);

    // Usar qDebug() para verificar si los datos se están ingresando
    for (Peliculas* p : vectorPelicula) {
        qDebug() << "Título: " << p->getTitulo();
        qDebug() << "Duración: " << p->getDuracion();
        qDebug() << "Género: " << p->getGenero();
        qDebug() << "Clasificación: " << p->getClasificacion();
        qDebug() << "Sinopsis: " << p->getSinopsis();
        qDebug() << "------";
    }

   emit peliAgregada(pelicula->getTitulo(), pelicula->getDuracion(), pelicula->getGenero(),
                      pelicula->getClasificacion(), pelicula->getSinopsis());

    accept(); // SE CIERRA EL DIALOGO
}

