#include "peliculas.h"
#include "ui_peliculas.h"

Peliculas::Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas),
    vectorPelicula(vectorPeliculaRef)
{
    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Peliculas");

    //SELECCIONAR MAS DE 99 EN EL SPINBOX
    ui->spinBox_duracion->setMaximum(200);

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    //Conectamos los botones a los slots
    connect(ui->Boton_buscar, &QPushButton::clicked, this, &Peliculas::buscarPelicula);
    connect(ui->Boton_agregar, &QPushButton::clicked, this, &Peliculas::agregarPelicula);
    connect(ui->Boton_modificar, &QPushButton::clicked, this, &Peliculas::modificarPelicula);
    connect(ui->Boton_eliimnar, &QPushButton::clicked, this, &Peliculas::eliminarPelicula);
    connect(ui->Boton_guardar, &QPushButton::clicked, this, &Peliculas::agregarPelicula);
}


Peliculas::~Peliculas()
{
    delete ui;
}

// GET Y SET DE TITULO

QString Peliculas::getTitulo() const{
    return Titulo;
}

void Peliculas::setTitulo(QString titulo){
    Titulo = titulo;
}

// GET Y SET DE DURACION

int Peliculas::getDuracion() const
{
    return Duracion;
}

void Peliculas::setDuracion(int duracion)
{
    Duracion = duracion;
}

// GET Y SET DE GENERO

QString Peliculas::getGenero() const
{
    return Genero;
}

void Peliculas::setGenero(QString genero)
{
    Genero = genero;
}

// GET Y SET DE CLASIFICACION
QString Peliculas::getClasificacion() const
{
    return Clasificacion;
}

void Peliculas::setClasificacion(QString clasificacion)
{
    Clasificacion = clasificacion;
}

// GET Y SET DE SINOPSIS
QString Peliculas::getSinopsis() const
{
    return Sinopsis;
}

void Peliculas::setSinopsis(QString sinopsis)
{
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
void Peliculas::agregarPelicula()
{
    Peliculas *pelicula = new Peliculas(vectorPelicula, this);

    pelicula->setTitulo(ui->lineEdit_nombre_completo->text());
    pelicula->setDuracion(ui->spinBox_duracion->value());
    pelicula->setGenero(ui->lineEdit_genero->text());
    pelicula->setClasificacion(ui->lineEdit_clasificacion->text());
    pelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText());

    vectorPelicula.push_back(pelicula);

    //Usar qDebug() para verificar si los datos se están ingresando
    for (Peliculas* p : vectorPelicula)
    {
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
void Peliculas::buscarPelicula()
{
    QString valor = ui->lineEdit_nombre->text();

    bool found = false;
    for(Peliculas *pelicula : vectorPelicula)
    {
        if(pelicula->getTitulo() == valor)
        {
            found = true;
            break;
        }
    }

    if(found)
    {
        QMessageBox::information(this, "Aviso", "La Pelicula se encuentra cargada");
    }
    else
    {
         QMessageBox::warning(this, "Advertencia", "Pelicula no encontrada");
    }
}

// BOTON QUE ELIMINA LA PELICULA
void Peliculas::eliminarPelicula()
{
    QString nombrePeli = ui->lineEdit_nombre->text();

    bool encontrado = false;

    for(auto it = vectorPelicula.begin(); it != vectorPelicula.end(); it++){
        if((*it)->getTitulo() == nombrePeli)
        { // SE UTILIZA (*it) PORQUE VectorPelicula ES UN PUNTERO A Peliculas
            vectorPelicula.erase(it);
            QMessageBox::information(this, "Aviso", "Se ha eliminado la pelicula");
            encontrado = true;
            break;
        }
    }

    if(!encontrado)
    {
        QMessageBox::warning(this, "Error", "No se ha eliminado la pelicula o no se encuentra en el sistema");
    }

}

// Método que modifica la información de una película en el vector
void Peliculas::modificarPelicula()
{
    QString nombrePeli = ui->lineEdit_nombre->text(); // Título de la película a modificar

    bool encontrado = false;

    // Buscar la película en el vector
    for(Peliculas *pelicula : vectorPelicula)
    {
        if(pelicula->getTitulo() == nombrePeli)
        {
            // Si la película existe, actualizamos sus valores
            pelicula->setTitulo(ui->lineEdit_nombre_completo->text());
            pelicula->setDuracion(ui->spinBox_duracion->value());
            pelicula->setGenero(ui->lineEdit_genero->text());
            pelicula->setClasificacion(ui->lineEdit_clasificacion->text());
            pelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText());

            QMessageBox::information(this, "Modificación", "Pelicula modificada exitosamente.");
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        QMessageBox::warning(this, "Error", "La película no se encuentra en el sistema para ser modificada.");
    }
}

void Peliculas::guardarCambios()
{

}
