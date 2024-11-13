#include "peliculas.h"
#include "ui_peliculas.h"

Peliculas::Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas),
    vectorPelicula(vectorPeliculaRef)
{
    ui->setupUi(this);

    // Titulo de la ventana
    this->setWindowTitle("Peliculas");
    // SELECCIONAR MAS DE 99 EN EL SPINBOX
    ui->spinBox->setMaximum(200);

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

// BOTON QUE AGREGA LA PELICULA AL VECTOR
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

}

    // BOTON PARA BUSCAR PELICULA
void Peliculas::on_pushButton_clicked()
{
    QString valor = ui->lineEdit->text();

    bool found = false;
    for(Peliculas *pelicula : vectorPelicula){
        if(pelicula->getTitulo() == valor){
            found = true;
            break;
        }
    }

    if(found){
        QMessageBox::information(this, "Aviso", "La Pelicula se encuentra cargada");
    } else {
         QMessageBox::warning(this, "Advertencia", "Pelicula no encontrada");
    }
}

// BOTON QUE ELIMINA LA PELICULA
void Peliculas::on_pushButton_4_clicked()
{
    QString nombrePeli = ui->lineEdit->text();

    bool encontrado = false;
    for(auto it = vectorPelicula.begin(); it != vectorPelicula.end(); it++){
        if((*it)->getTitulo() == nombrePeli){ // SE UTILIZA (*it) PORQUE VectorPelicula ES UN PUNTERO A Peliculas
            vectorPelicula.erase(it);
            QMessageBox::information(this, "Aviso", "Se ha eliminado la pelicula");
            encontrado = true;
            break;
        }
    }

    if(!encontrado){
        QMessageBox::warning(this, "Error", "No se ha eliminado la pelicula o no se encuentra en el sistema");
    }

}

