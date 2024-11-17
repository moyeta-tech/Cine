#include "peliculas.h"
#include "ui_peliculas.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <vector>

Peliculas::Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas),
    vectorPelicula(vectorPeliculaRef)
{
    ui->setupUi(this);

    this->setWindowTitle("Peliculas");

    ui->spinBox_duracion->setMaximum(200);

    initstylesheet();

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

QString Peliculas::getTitulo() const {
    return Titulo;
}

void Peliculas::setTitulo(QString titulo) {
    Titulo = titulo;
}

// GET Y SET DE DURACION

int Peliculas::getDuracion() const {
    return Duracion;
}

void Peliculas::setDuracion(int duracion) {
    Duracion = duracion;
}

// GET Y SET DE GENERO

QString Peliculas::getGenero() const {
    return Genero;
}

void Peliculas::setGenero(QString genero) {
    Genero = genero;
}

// GET Y SET DE CLASIFICACION

QString Peliculas::getClasificacion() const {
    return Clasificacion;
}

void Peliculas::setClasificacion(QString clasificacion) {
    Clasificacion = clasificacion;
}

// GET Y SET DE SINOPSIS

QString Peliculas::getSinopsis() const {
    return Sinopsis;
}

void Peliculas::setSinopsis(QString sinopsis) {
    Sinopsis = sinopsis;
}

// Métodos para obtener el horario y el día

QTime Peliculas::getHorario() const {
    return horario;
}

void Peliculas::setHorario(const QTime &h) {
    horario = h;
}

QDate Peliculas::getDia() const {
    return dia;
}

void Peliculas::setDia(const QDate &d) {
    dia = d;
}

void Peliculas::initstylesheet() {
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " << styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

// BOTON QUE AGREGA LA PELICULA AL VECTOR

void Peliculas::agregarPelicula() {
    Peliculas *pelicula = new Peliculas(vectorPelicula, this);

    pelicula->setTitulo(ui->lineEdit_nombre_completo->text());
    pelicula->setDuracion(ui->spinBox_duracion->value());
    pelicula->setGenero(ui->lineEdit_genero->text());
    pelicula->setClasificacion(ui->lineEdit_clasificacion->text());
    pelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText());

    pelicula->setHorario(ui->timeEdit->time());
    pelicula->setDia(ui->dateEdit->date());

    vectorPelicula.push_back(pelicula);

    for (Peliculas* p : vectorPelicula) {
        qDebug() << "Título: " << p->getTitulo();
        qDebug() << "Duración: " << p->getDuracion();
        qDebug() << "Género: " << p->getGenero();
        qDebug() << "Clasificación: " << p->getClasificacion();
        qDebug() << "Sinopsis: " << p->getSinopsis();
        qDebug() << "Horario: " << p->getHorario().toString();
        qDebug() << "Día: " << p->getDia().toString();
        qDebug() << "------";
    }

    emit peliAgregada(pelicula->getTitulo(), pelicula->getDuracion(), pelicula->getGenero(),
                      pelicula->getClasificacion(), pelicula->getSinopsis(), pelicula->getHorario(), pelicula->getDia());
}

// BOTON PARA BUSCAR PELICULA

void Peliculas::buscarPelicula() {
    QString valor = ui->lineEdit_nombre->text();
    bool found = false;

    for (Peliculas *pelicula : vectorPelicula) {
        if (pelicula->getTitulo() == valor) {
            found = true;
            qDebug() << "Película encontrada:";
            qDebug() << "Título: " << pelicula->getTitulo();
            qDebug() << "Duración: " << pelicula->getDuracion();
            qDebug() << "Género: " << pelicula->getGenero();
            qDebug() << "Clasificación: " << pelicula->getClasificacion();
            qDebug() << "Sinopsis: " << pelicula->getSinopsis();
            qDebug() << "Horario: " << pelicula->getHorario().toString();
            qDebug() << "Día: " << pelicula->getDia().toString();
            break;
        }
    }

    if (found) {
        QMessageBox::information(this, "Aviso", "La Película se encuentra cargada");
    } else {
        QMessageBox::warning(this, "Advertencia", "Película no encontrada");
    }
}

// BOTON QUE ELIMINA LA PELICULA

void Peliculas::eliminarPelicula() {
    QString nombrePeli = ui->lineEdit_nombre->text();
    bool encontrado = false;

    for (auto it = vectorPelicula.begin(); it != vectorPelicula.end(); it++) {
        if ((*it)->getTitulo() == nombrePeli) {
            vectorPelicula.erase(it);
            QMessageBox::information(this, "Aviso", "Se ha eliminado la película");
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        QMessageBox::warning(this, "Error", "No se ha eliminado la película o no se encuentra en el sistema");
    }
}

// Método que modifica la información de una película en el vector

void Peliculas::modificarPelicula() {
    QString nombrePeli = ui->lineEdit_nombre->text();
    bool encontrado = false;

    for (Peliculas* pelicula : vectorPelicula) {
        if (pelicula->getTitulo() == nombrePeli) {
            pelicula->setDuracion(ui->spinBox_duracion->value());
            pelicula->setGenero(ui->lineEdit_genero->text());
            pelicula->setClasificacion(ui->lineEdit_clasificacion->text());
            pelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText());
            pelicula->setHorario(ui->timeEdit->time());
            pelicula->setDia(ui->dateEdit->date());

            QMessageBox::information(this, "Éxito", "La película ha sido modificada correctamente");
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        QMessageBox::warning(this, "Error", "Película no encontrada para modificar");
    }
}

// Método para cargar las películas desde un archivo de texto
std::vector<Peliculas*> Peliculas::cargarPeliculas(const QString &archivo)
{
    QFile file(archivo);
    std::vector<Peliculas*> peliculasList;  // Usamos std::vector aquí

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(',');

            Peliculas* p = new Peliculas(peliculasList);  // Ya no hay problemas de conversión

            // Aquí puedes agregar el código para asignar los atributos a 'p' (nombre, género, etc.)
            peliculasList.push_back(p);  // Agregar la película al vector
        }
        file.close();
    }
    return peliculasList;  // Retornamos el vector
}
