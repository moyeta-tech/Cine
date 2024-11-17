#include "peliculas.h"
#include "ui_peliculas.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <vector>
#include <QMessageBox>

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
QList<QTime> Peliculas::getHorarios() const {
    return horarios;
}

void Peliculas::setHorarios(const QList<QTime> &horarios) {
    this->horarios = horarios;
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
void Peliculas::agregarPelicula()
{
    Peliculas *pelicula = new Peliculas(vectorPelicula, this);

    pelicula->setTitulo(ui->lineEdit_nombre_completo->text());
    pelicula->setDuracion(ui->spinBox_duracion->value());
    pelicula->setGenero(ui->lineEdit_genero->text());
    pelicula->setClasificacion(ui->lineEdit_clasificacion->text());
    pelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText());

    // Obtener los horarios de los 4 timeEdit
    QList<QTime> horarios;
    horarios.append(ui->timeEdit->time());
    horarios.append(ui->timeEdit_2->time());
    horarios.append(ui->timeEdit_3->time());
    horarios.append(ui->timeEdit_4->time());

    pelicula->setHorarios(horarios);
    pelicula->setDia(ui->dateEdit->date());

    vectorPelicula.push_back(pelicula);

    // Imprimir los detalles de las películas en el vector
    for (Peliculas* p : vectorPelicula) {
        qDebug() << "Título: " << p->getTitulo();
        qDebug() << "Duración: " << p->getDuracion();
        qDebug() << "Género: " << p->getGenero();
        qDebug() << "Clasificación: " << p->getClasificacion();
        qDebug() << "Sinopsis: " << p->getSinopsis();
        qDebug() << "Horarios: ";
        for (const QTime &h : p->getHorarios()) {
            qDebug() << h.toString();
        }
        qDebug() << "Día: " << p->getDia().toString();
        qDebug() << "------";
    }

    emit peliAgregada(pelicula->getTitulo(), pelicula->getDuracion(), pelicula->getGenero(),
                      pelicula->getClasificacion(), pelicula->getSinopsis(), pelicula->getHorarios(), pelicula->getDia());
}

// BOTON PARA BUSCAR PELICULA
void Peliculas::buscarPelicula() {
    QString valor = ui->lineEdit_nombre->text();
    bool found = false;

    // Limpiar los campos de la interfaz antes de la búsqueda
    ui->lineEdit_genero->clear();
    ui->lineEdit_clasificacion->clear();
    ui->textEdit_sinopsis->clear();
    ui->spinBox_duracion->setValue(0);
    ui->timeEdit->clear();
    ui->timeEdit_2->clear();
    ui->timeEdit_3->clear();
    ui->timeEdit_4->clear();
    ui->dateEdit->clear();

    for (Peliculas *pelicula : vectorPelicula) {
        if (pelicula->getTitulo() == valor) {
            found = true;
            // Mostrar la información de la película en los campos correspondientes
            ui->lineEdit_genero->setText(pelicula->getGenero());
            ui->lineEdit_clasificacion->setText(pelicula->getClasificacion());
            ui->textEdit_sinopsis->setPlainText(pelicula->getSinopsis());
            ui->spinBox_duracion->setValue(pelicula->getDuracion());

            // Actualizar los horarios en los time edits
            QList<QTime> horarios = pelicula->getHorarios();
            if (horarios.size() >= 4) {
                ui->timeEdit->setTime(horarios[0]);
                ui->timeEdit_2->setTime(horarios[1]);
                ui->timeEdit_3->setTime(horarios[2]);
                ui->timeEdit_4->setTime(horarios[3]);
            }

            // Mostrar la fecha
            ui->dateEdit->setDate(pelicula->getDia());

            QMessageBox::information(this, "Aviso", "La Película se encuentra cargada");
            break;
        }
    }

    if (!found) {
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
            QList<QTime> horarios;
            horarios.append(ui->timeEdit->time());
            horarios.append(ui->timeEdit_2->time());
            horarios.append(ui->timeEdit_3->time());
            horarios.append(ui->timeEdit_4->time());
            pelicula->setHorarios(horarios);
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

// Método estático para cargar películas desde un archivo
std::vector<Peliculas*> Peliculas::cargarPeliculas(const QString &rutaArchivo) {
    std::vector<Peliculas*> peliculasCargadas;

    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "No se pudo abrir el archivo de películas.";
        return peliculasCargadas;
    }

    QTextStream entrada(&archivo);
    while (!entrada.atEnd()) {
        QString linea = entrada.readLine();
        if (!linea.isEmpty()) {
            peliculasCargadas.push_back(new Peliculas(peliculasCargadas)); // Usar el constructor existente
        }
    }
    archivo.close();

    return peliculasCargadas;
}
