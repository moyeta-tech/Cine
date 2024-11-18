#include "peliculas.h"
#include "ui_peliculas.h"

#include <QFile>
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

//////////////////////////////////////////
// GETTERS Y SETTERS
//////////////////////////////////////////

QString Peliculas::getTitulo() const {
    return Titulo;
}

void Peliculas::setTitulo(QString titulo) {
    Titulo = titulo;
}

int Peliculas::getDuracion() const {
    return Duracion;
}

void Peliculas::setDuracion(int duracion) {
    Duracion = duracion;
}

QString Peliculas::getGenero() const {
    return Genero;
}

void Peliculas::setGenero(QString genero) {
    Genero = genero;
}

QString Peliculas::getClasificacion() const {
    return Clasificacion;
}

void Peliculas::setClasificacion(QString clasificacion) {
    Clasificacion = clasificacion;
}

QString Peliculas::getSinopsis() const {
    return Sinopsis;
}

void Peliculas::setSinopsis(QString sinopsis) {
    Sinopsis = sinopsis;
}

QList<QTime> Peliculas::getHorarios() const {
    return this->horarios;
}

void Peliculas::setHorarios(const QList<QTime> &horarios) {
    this->horarios = horarios;
}

QDate Peliculas::getDia() const {
    return this->dia;
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

void Peliculas::agregarPelicula()
{
    // Obtener los datos de la interfaz gráfica
    QString titulo = ui->lineEdit_nombre_completo->text();
    int duracion = ui->spinBox_duracion->value();
    QString genero = ui->lineEdit_genero->text();
    QString clasificacion = ui->lineEdit_clasificacion->text();
    QString sinopsis = ui->textEdit_sinopsis->toPlainText();
    QDate dia = ui->dateEdit->date();

    // Obtener los horarios desde los QTimeEdit
    QList<QTime> horarios;
    horarios.append(ui->timeEdit->time()); // QTimeEdit para el primer horario
    horarios.append(ui->timeEdit_2->time()); // QTimeEdit para el segundo horario
    horarios.append(ui->timeEdit_3->time()); // QTimeEdit para el tercer horario
    horarios.append(ui->timeEdit_4->time()); // QTimeEdit para el cuarto horario

    // Crear la nueva película con los datos recogidos
    Peliculas* nuevaPelicula = new Peliculas(vectorPelicula);
    nuevaPelicula->setTitulo(titulo);
    nuevaPelicula->setDuracion(duracion);
    nuevaPelicula->setGenero(genero);
    nuevaPelicula->setClasificacion(clasificacion);
    nuevaPelicula->setSinopsis(sinopsis);
    nuevaPelicula->setHorarios(horarios);
    nuevaPelicula->setDia(dia);

    // Agregar la nueva película al vector
    vectorPelicula.push_back(nuevaPelicula);

    // Mostrar un mensaje de éxito
    QMessageBox::information(this, "Película Agregada", "La película se ha agregado correctamente.");
}



void Peliculas::buscarPelicula() {
    QString valor = ui->lineEdit_nombre->text();
    bool found = false;

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
            ui->lineEdit_genero->setText(pelicula->getGenero());
            ui->lineEdit_clasificacion->setText(pelicula->getClasificacion());
            ui->textEdit_sinopsis->setPlainText(pelicula->getSinopsis());
            ui->spinBox_duracion->setValue(pelicula->getDuracion());

            QList<QTime> horarios = pelicula->getHorarios();
            if (horarios.size() >= 4) {
                ui->timeEdit->setTime(horarios[0]);
                ui->timeEdit_2->setTime(horarios[1]);
                ui->timeEdit_3->setTime(horarios[2]);
                ui->timeEdit_4->setTime(horarios[3]);
            }

            ui->dateEdit->setDate(pelicula->getDia());

            QMessageBox::information(this, "Aviso", "La Película se encuentra cargada");
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Advertencia", "Película no encontrada");
    }
}

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

            QMessageBox::information(this, "Aviso", "Se ha modificado la película");
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        QMessageBox::warning(this, "Error", "Película no encontrada");
    }
}

