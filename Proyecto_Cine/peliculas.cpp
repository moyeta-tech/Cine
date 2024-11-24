#include "peliculas.h"
#include "ui_peliculas.h"

#include <QFile>
#include <QStringList>
#include <vector>
#include <QMessageBox>

Peliculas::Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas),
    vectorPelicula(vectorPeliculaRef),
    archivoCSV("peliculas.csv")  // Ruta por defecto para el archivo CSV
{
    ui->setupUi(this);
    this->setWindowTitle("Peliculas");
    ui->spinBox_duracion->setMaximum(200);

    initstylesheet();

    connect(ui->Boton_buscar, &QPushButton::clicked, this, &Peliculas::buscarPelicula);
    connect(ui->Boton_agregar, &QPushButton::clicked, this, &Peliculas::agregarPelicula);
    connect(ui->Boton_modificar, &QPushButton::clicked, this, &Peliculas::modificarPelicula);
    connect(ui->Boton_eliimnar, &QPushButton::clicked, this, &Peliculas::eliminarPelicula);

    cargarPeliculasDesdeCSV(archivoCSV);  // Cargar las películas al inicio desde el CSV
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

// Función para guardar las películas en un archivo CSV
void Peliculas::guardarPeliculasEnCSV(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para guardar.");
        return;
    }

    QTextStream out(&file);
    for (Peliculas* pelicula : vectorPelicula) {
        out << pelicula->getTitulo() << ","
            << pelicula->getDuracion() << ","
            << pelicula->getGenero() << ","
            << pelicula->getClasificacion() << ","
            << pelicula->getSinopsis() << ","
            << pelicula->getDia().toString("yyyy-MM-dd") << ",";

        // Guardar horarios
        for (int i = 0; i < pelicula->getHorarios().size(); ++i) {
            out << pelicula->getHorarios()[i].toString("HH:mm");
            if (i != pelicula->getHorarios().size() - 1) {
                out << ";"; // Separar horarios por punto y coma
            }
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "Éxito", "Películas guardadas correctamente.");
}

// Función para cargar las películas desde un archivo CSV
void Peliculas::cargarPeliculasDesdeCSV(const QString &filename) {
    QFile file(filename);

    // Comprobar si el archivo existe
    if (!file.exists()) {
        qDebug() << "El archivo no existe, creando uno nuevo.";
        // Si el archivo no existe, podemos crearlo vacío
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "No se pudo crear el archivo.");
            return;
        }
        file.close();
        return; // Salir de la función
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para cargar.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() < 7) continue;

        Peliculas* nuevaPelicula = new Peliculas(vectorPelicula);

        nuevaPelicula->setTitulo(fields[0]);
        nuevaPelicula->setDuracion(fields[1].toInt());
        nuevaPelicula->setGenero(fields[2]);
        nuevaPelicula->setClasificacion(fields[3]);
        nuevaPelicula->setSinopsis(fields[4]);
        nuevaPelicula->setDia(QDate::fromString(fields[5], "yyyy-MM-dd"));

        // Leer los horarios
        QStringList horarios = fields[6].split(";");
        QList<QTime> listaHorarios;
        for (const QString &hora : horarios) {
            listaHorarios.append(QTime::fromString(hora, "HH:mm"));
        }
        nuevaPelicula->setHorarios(listaHorarios);

        vectorPelicula.push_back(nuevaPelicula);
    }

    file.close();
    QMessageBox::information(this, "Éxito", "Películas cargadas correctamente.");
}

// Función para agregar una nueva película
void Peliculas::agregarPelicula() {
    QString titulo = ui->lineEdit_nombre_completo->text();
    int duracion = ui->spinBox_duracion->value();
    QString genero = ui->lineEdit_genero->text();
    QString clasificacion = ui->lineEdit_clasificacion->text();
    QString sinopsis = ui->textEdit_sinopsis->toPlainText();
    QDate dia = ui->dateEdit->date();

    QList<QTime> horarios;
    horarios.append(ui->timeEdit->time());
    horarios.append(ui->timeEdit_2->time());
    horarios.append(ui->timeEdit_3->time());
    horarios.append(ui->timeEdit_4->time());

    Peliculas* nuevaPelicula = new Peliculas(vectorPelicula);
    nuevaPelicula->setTitulo(titulo);
    nuevaPelicula->setDuracion(duracion);
    nuevaPelicula->setGenero(genero);
    nuevaPelicula->setClasificacion(clasificacion);
    nuevaPelicula->setSinopsis(sinopsis);
    nuevaPelicula->setHorarios(horarios);
    nuevaPelicula->setDia(dia);

    vectorPelicula.push_back(nuevaPelicula);

    guardarPeliculasEnCSV(archivoCSV);  // Guardar el archivo después de agregar la película

    QMessageBox::information(this, "Película Agregada", "La película se ha agregado correctamente.");
}

// Función para buscar una película
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
            ui->textEdit_sinopsis->setText(pelicula->getSinopsis());
            ui->spinBox_duracion->setValue(pelicula->getDuracion());
            ui->timeEdit->setTime(pelicula->getHorarios().at(0));
            ui->timeEdit_2->setTime(pelicula->getHorarios().at(1));
            ui->timeEdit_3->setTime(pelicula->getHorarios().at(2));
            ui->timeEdit_4->setTime(pelicula->getHorarios().at(3));
            ui->dateEdit->setDate(pelicula->getDia());
            break;
        }
    }

    if (!found) {
        QMessageBox::information(this, "No Encontrado", "No se encontró la película.");
    }
}

void Peliculas::modificarPelicula() {
    QString valor = ui->lineEdit_nombre->text();
    bool found = false;

    for (Peliculas *pelicula : vectorPelicula) {
        if (pelicula->getTitulo() == valor) {
            found = true;

            // Modificar los datos
            pelicula->setDuracion(ui->spinBox_duracion->value());
            pelicula->setGenero(ui->lineEdit_genero->text());
            pelicula->setClasificacion(ui->lineEdit_clasificacion->text());
            pelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText());
            pelicula->setDia(ui->dateEdit->date());

            QList<QTime> horarios;
            horarios.append(ui->timeEdit->time());
            horarios.append(ui->timeEdit_2->time());
            horarios.append(ui->timeEdit_3->time());
            horarios.append(ui->timeEdit_4->time());
            pelicula->setHorarios(horarios);

            guardarPeliculasEnCSV(archivoCSV);  // Guardar el archivo después de modificar

            QMessageBox::information(this, "Película Modificada", "La película ha sido modificada.");
            break;
        }
    }

    if (!found) {
        QMessageBox::information(this, "No Encontrada", "No se encontró la película.");
    }
}

void Peliculas::eliminarPelicula() {
    QString valor = ui->lineEdit_nombre->text();
    bool found = false;

    for (auto it = vectorPelicula.begin(); it != vectorPelicula.end(); ++it) {
        if ((*it)->getTitulo() == valor) {
            found = true;
            delete *it;
            vectorPelicula.erase(it);
            guardarPeliculasEnCSV(archivoCSV);  // Guardar el archivo después de eliminar
            QMessageBox::information(this, "Película Eliminada", "La película ha sido eliminada.");
            break;
        }
    }

    if (!found) {
        QMessageBox::information(this, "No Encontrada", "No se encontró la película.");
    }
}
