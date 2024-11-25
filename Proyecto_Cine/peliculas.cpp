#include "peliculas.h"
#include "ui_peliculas.h"

#include <QFile>
#include <QStringList>
#include <vector>
#include <QMessageBox>
#include <QDebug>

Peliculas::Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas),
    vectorPelicula(vectorPeliculaRef),
    archivoCSV("peliculas.csv")  // Ruta por defecto para el archivo CSV
{
    qDebug() << "Constructor iniciado.";
    ui->setupUi(this);
    qDebug() << "UI configurada.";

    this->setWindowTitle("Peliculas");
    ui->spinBox_duracion->setMaximum(200);

    initstylesheet();
    qDebug() << "Stylesheet inicializado.";

    connect(ui->Boton_buscar, &QPushButton::clicked, this, &Peliculas::buscarPelicula);
    connect(ui->Boton_agregar, &QPushButton::clicked, this, &Peliculas::agregarPelicula);
  //  connect(ui->Boton_modificar, &QPushButton::clicked, this, &Peliculas::modificarPelicula);
    connect(ui->Boton_eliimnar, &QPushButton::clicked, this, &Peliculas::eliminarPelicula);

}

Peliculas::~Peliculas()
{
    delete ui;
    qDebug() << "Destructor llamado. UI eliminada.";
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
    qDebug() << "Apertura de archivo de estilo: " << styleOK;
    if (styleOK) {
        QString stringEstilo = QString::fromLatin1(style.readAll());
        this->setStyleSheet(stringEstilo);
    } else {
        qDebug() << "No se pudo abrir el archivo de estilo.";
    }
}

// Función para guardar las películas en un archivo CSV
void Peliculas::guardarPeliculasEnCSV(const QString &filename) {
    qDebug() << "Guardando películas en CSV...";
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error al intentar abrir el archivo para guardar.";
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
        const QList<QTime>& horarios = pelicula->getHorarios();
        for (int i = 0; i < horarios.size(); ++i) {
            if(horarios[i].isValid()){
                out << horarios[i].toString("HH:mm");
                if(i != horarios.size() - 1){
                    out << ";";
                }
            } else {
                qDebug() << "Horario inválido detectado y no guardado.";
            }

        }
        out << "\n";
    }

    file.close();
    qDebug() << "Películas guardadas correctamente en el archivo.";
}

void Peliculas::cargarPeliculasDesdeCSV(const QString &filename) {
    qDebug() << "Cargando películas desde CSV...";

    QFile file(filename);

    // Comprobar si el archivo existe
    if (!file.exists()) {
        qDebug() << "El archivo no existe, creando uno nuevo.";
        // Si el archivo no existe, podemos crearlo vacío
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "No se pudo crear el archivo.";
            QMessageBox::warning(this, "Error", "No se pudo crear el archivo.");
            return;
        }
        file.close();
        return; // Salir de la función
    }

    // Intentamos abrir el archivo en modo lectura de texto con codificación UTF-8
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error al intentar abrir el archivo CSV.";
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para cargar.");
        return;
    }

    // Abrir el archivo con codificación UTF-8 directamente
    QTextStream in(&file);
    in.setAutoDetectUnicode(true);  // Esto detectará automáticamente la codificación, y Qt intentará manejar la codificación correctamente

    // Limpiar el vector antes de cargar los nuevos datos
    qDeleteAll(vectorPelicula);  // Eliminar todas las películas previas del vector
    vectorPelicula.clear();       // Limpiar el vector

    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << "Procesando línea: " << line;
        QStringList fields = line.split(",");

        // Verificar que haya suficientes campos en la línea
        if (fields.size() < 7) {
            qDebug() << "Línea ignorada, número de campos insuficiente: " << line;
            continue;
        }

        Peliculas* nuevaPelicula = new Peliculas(vectorPelicula);
        nuevaPelicula->setTitulo(fields[0]);
        nuevaPelicula->setDuracion(fields[1].toInt());
        nuevaPelicula->setGenero(fields[2]);
        nuevaPelicula->setClasificacion(fields[3]);
        nuevaPelicula->setSinopsis(fields[4]);
        nuevaPelicula->setDia(QDate::fromString(fields[5], "yyyy-MM-dd"));

        // Leer los horarios (los horarios están separados por tabuladores en el CSV)
        QStringList horarios = fields[6].split(";"); // Asumiendo que los horarios están separados por tabuladores
        QList<QTime> listaHorarios;
        for (const QString &hora : horarios) {
            QTime horario = QTime::fromString(hora, "HH:mm");
            if(horario.isValid()){
                listaHorarios.append(horario);
            } else {
                qDebug() << "Horario invalido ignorado: " << hora;
            }
        }
        nuevaPelicula->setHorarios(listaHorarios);

        // Agregar la nueva película al vector
        vectorPelicula.push_back(nuevaPelicula);
    }

    file.close();
    qDebug() << "Películas cargadas correctamente desde el archivo.";
}



void Peliculas::agregarPelicula() {
    // Crear una nueva película a partir de los datos ingresados en la interfaz
    Peliculas* nuevaPelicula = new Peliculas(vectorPelicula);
    nuevaPelicula->setTitulo(ui->lineEdit_nombre->text().trimmed());
    nuevaPelicula->setDuracion(ui->spinBox_duracion->value());
    nuevaPelicula->setGenero(ui->lineEdit_genero->text().trimmed());
    nuevaPelicula->setClasificacion(ui->lineEdit_clasificacion->text().trimmed());
    nuevaPelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText().trimmed());
    nuevaPelicula->setDia(ui->dateEdit->date());

    // Crear la lista de horarios y agregar los valores de los QTimeEdit
    QList<QTime> horarios;
    if (ui->timeEdit->time().isValid()) horarios.append(ui->timeEdit->time());
    if (ui->timeEdit_2->time().isValid()) horarios.append(ui->timeEdit_2->time());
    if (ui->timeEdit_3->time().isValid()) horarios.append(ui->timeEdit_3->time());
    if (ui->timeEdit_4->time().isValid()) horarios.append(ui->timeEdit_4->time());

    if (horarios.isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe ingresar al menos un horario válido.");
        return;
    }

    nuevaPelicula->setHorarios(horarios); // Asignar los horarios a la película

    // Agregar la nueva película al vector
    vectorPelicula.push_back(nuevaPelicula);

    // Guardar las películas actualizadas en el archivo CSV
    guardarPeliculasEnCSV(archivoCSV);

    // Notificar al usuario
    QMessageBox::information(this, "Éxito", "Película agregada correctamente.");
}

void Peliculas::buscarPelicula() {
    QString valor = ui->lineEdit_nombre->text();
    if (valor.isEmpty()) {
        qDebug() << "El campo de búsqueda está vacío.";
        return;
    }

    for (Peliculas* pelicula : vectorPelicula) {
        if (pelicula->getTitulo().contains(valor, Qt::CaseInsensitive)) {
            qDebug() << "Película encontrada: " << pelicula->getTitulo();
            ui->lineEdit_genero->setText(pelicula->getGenero());
            ui->lineEdit_clasificacion->setText(pelicula->getClasificacion());
            ui->textEdit_sinopsis->setPlainText(pelicula->getSinopsis());
            ui->spinBox_duracion->setValue(pelicula->getDuracion());
            ui->dateEdit->setDate(pelicula->getDia());
            break;
        }
    }
}



void Peliculas::eliminarPelicula() {
    QString tituloEliminar = ui->lineEdit_buscar->text().trimmed();

    if (tituloEliminar.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor ingrese un título para eliminar.");
        return;
    }

    bool encontrada = false;
    for (auto it = vectorPelicula.begin(); it != vectorPelicula.end(); ++it) {
        if ((*it)->getTitulo().compare(tituloEliminar, Qt::CaseInsensitive) == 0) {
            // Si la película es encontrada, eliminarla del vector
            delete *it; // Eliminar el objeto de memoria
            vectorPelicula.erase(it); // Eliminarla del vector
            encontrada = true;
            break;
        }
    }

    if (encontrada) {
        guardarPeliculasEnCSV(archivoCSV); // Guardar los cambios en el archivo CSV
        QMessageBox::information(this, "Éxito", "Película eliminada correctamente.");
        ui->lineEdit_buscar->clear(); // Limpiar el campo de búsqueda
    } else {
        QMessageBox::information(this, "No encontrada", "No se encontró una película con ese título.");
    }
}

/*
void Peliculas::modificarPelicula() {
    QString tituloModificar = ui->lineEdit_buscar->text().trimmed();

    if (tituloModificar.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor ingrese un título para modificar.");
        return;
    }

    bool encontrada = false;
    for (Peliculas* pelicula : vectorPelicula) {
        if (pelicula->getTitulo().compare(tituloModificar, Qt::CaseInsensitive) == 0) {
            // Modificar los datos de la película
            pelicula->setTitulo(ui->lineEdit_nombre->text());
            pelicula->setDuracion(ui->spinBox_duracion->value());
            pelicula->setGenero(ui->lineEdit_genero->text());
            pelicula->setClasificacion(ui->lineEdit_clasificacion->text());
            pelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText());
            pelicula->setDia(ui->dateEdit->date());

            // Crear la lista de horarios modificada
            QList<QTime> horarios;
            if (ui->timeEdit->time().isValid()) horarios.append(ui->timeEdit->time());
            if (ui->timeEdit_2->time().isValid()) horarios.append(ui->timeEdit_2->time());
            if (ui->timeEdit_3->time().isValid()) horarios.append(ui->timeEdit_3->time());
            if (ui->timeEdit_4->time().isValid()) horarios.append(ui->timeEdit_4->time());

            if (horarios.isEmpty()) {
                QMessageBox::warning(this, "Error", "Debe ingresar al menos un horario.");
                return;
            }

            pelicula->setHorarios(horarios);
            encontrada = true;
            break;
        }
    }

    if (encontrada) {
        guardarPeliculasEnCSV(archivoCSV); // Guardar los cambios en el archivo CSV
        QMessageBox::information(this, "Éxito", "Película modificada correctamente.");
        ui->lineEdit_buscar->clear(); // Limpiar el campo de búsqueda
    } else {
        QMessageBox::information(this, "No encontrada", "No se encontró una película con ese título.");
    }
}
*/
