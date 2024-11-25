#include "peliculas.h"
#include "ui_peliculas.h"

#include <QFile>
#include <QStringList>
#include <vector>
#include <QMessageBox>
#include <QDebug>

// Constructor de la clase Peliculas
Peliculas::Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peliculas),
    vectorPelicula(vectorPeliculaRef),
    archivoCSV("peliculas.csv")  // Ruta por defecto para el archivo CSV
{
    qDebug() << "Constructor iniciado.";  // Mensaje de depuración
    ui->setupUi(this);  // Configura la interfaz de usuario
    qDebug() << "UI configurada.";

    this->setWindowTitle("Peliculas");  // Establece el título de la ventana
    ui->spinBox_duracion->setMaximum(200);  // Establece el máximo para duración de la película

    initstylesheet();  // Inicializa el estilo de la ventana
    qDebug() << "Stylesheet inicializado.";  // Mensaje de depuración

    // Conexiones entre botones y sus funciones
    connect(ui->Boton_buscar, &QPushButton::clicked, this, &Peliculas::buscarPelicula);  // Botón de búsqueda
    connect(ui->Boton_agregar, &QPushButton::clicked, this, &Peliculas::agregarPelicula);  // Botón de agregar
    // connect(ui->Boton_modificar, &QPushButton::clicked, this, &Peliculas::modificarPelicula);  // Botón de modificar (comentado)
    connect(ui->Boton_eliimnar, &QPushButton::clicked, this, &Peliculas::eliminarPelicula);  // Botón de eliminar
}

// Destructor que limpia los recursos
Peliculas::~Peliculas()
{
    delete ui;  // Elimina la interfaz de usuario
    qDebug() << "Destructor llamado. UI eliminada.";  // Mensaje de depuración
}

// Getters y setters para los atributos de la clase
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

// Función para inicializar el estilo de la ventana
void Peliculas::initstylesheet() {
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Ruta del archivo CSS
    bool styleOK = style.open(QFile::ReadOnly);  // Intenta abrir el archivo CSS en modo solo lectura
    qDebug() << "Apertura de archivo de estilo: " << styleOK;  // Mensaje de depuración
    if (styleOK) {
        QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el contenido del archivo CSS
        this->setStyleSheet(stringEstilo);  // Aplica el estilo a la ventana
    } else {
        qDebug() << "No se pudo abrir el archivo de estilo.";  // Mensaje de error si no se pudo abrir el archivo
    }
}

// Función para guardar las películas en un archivo CSV
void Peliculas::guardarPeliculasEnCSV(const QString &filename) {
    qDebug() << "Guardando películas en CSV...";  // Mensaje de depuración
    QFile file(filename);  // Abre el archivo para escritura
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error al intentar abrir el archivo para guardar.";  // Mensaje de error
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para guardar.");  // Muestra un cuadro de mensaje
        return;
    }

    QTextStream out(&file);  // Prepara un flujo de texto para escribir en el archivo
    for (Peliculas* pelicula : vectorPelicula) {  // Itera sobre todas las películas
        out << pelicula->getTitulo() << ","
            << pelicula->getDuracion() << ","
            << pelicula->getGenero() << ","
            << pelicula->getClasificacion() << ","
            << pelicula->getSinopsis() << ","
            << pelicula->getDia().toString("yyyy-MM-dd") << ",";

        // Guardar horarios
        const QList<QTime>& horarios = pelicula->getHorarios();  // Obtiene los horarios de la película
        for (int i = 0; i < horarios.size(); ++i) {  // Itera sobre los horarios
            if(horarios[i].isValid()){  // Verifica que el horario sea válido
                out << horarios[i].toString("HH:mm");  // Guarda el horario en el archivo
                if(i != horarios.size() - 1){
                    out << ";";  // Separa los horarios con punto y coma
                }
            } else {
                qDebug() << "Horario inválido detectado y no guardado.";  // Mensaje de depuración si el horario es inválido
            }
        }
        out << "\n";  // Salto de línea al final de cada película
    }

    file.close();  // Cierra el archivo
    qDebug() << "Películas guardadas correctamente en el archivo.";  // Mensaje de depuración
}

// Función para cargar las películas desde un archivo CSV
void Peliculas::cargarPeliculasDesdeCSV(const QString &filename) {
    qDebug() << "Cargando películas desde CSV...";  // Mensaje de depuración

    QFile file(filename);  // Abre el archivo
    // Comprobar si el archivo existe
    if (!file.exists()) {
        qDebug() << "El archivo no existe, creando uno nuevo.";  // Mensaje de depuración
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "No se pudo crear el archivo.";  // Mensaje de error
            QMessageBox::warning(this, "Error", "No se pudo crear el archivo.");  // Muestra un cuadro de mensaje
            return;
        }
        file.close();  // Cierra el archivo
        return;  // Sale de la función si no existe el archivo
    }

    // Intentamos abrir el archivo en modo lectura de texto con codificación UTF-8
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error al intentar abrir el archivo CSV.";  // Mensaje de error
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para cargar.");  // Muestra un cuadro de mensaje
        return;
    }

    QTextStream in(&file);  // Prepara un flujo de texto para leer el archivo
    in.setAutoDetectUnicode(true);  // Detecta automáticamente la codificación del archivo

    qDeleteAll(vectorPelicula);  // Elimina todas las películas previas del vector
    vectorPelicula.clear();  // Limpia el vector

    while (!in.atEnd()) {  // Mientras no se haya llegado al final del archivo
        QString line = in.readLine();  // Lee una línea del archivo
        qDebug() << "Procesando línea: " << line;  // Mensaje de depuración
        QStringList fields = line.split(",");  // Separa los campos por coma

        // Verificar que haya suficientes campos en la línea
        if (fields.size() < 7) {
            qDebug() << "Línea ignorada, número de campos insuficiente: " << line;  // Mensaje de depuración
            continue;  // Salta esta línea si no tiene suficientes campos
        }

        Peliculas* nuevaPelicula = new Peliculas(vectorPelicula);  // Crea una nueva película
        nuevaPelicula->setTitulo(fields[0]);  // Asigna el título
        nuevaPelicula->setDuracion(fields[1].toInt());  // Asigna la duración
        nuevaPelicula->setGenero(fields[2]);  // Asigna el género
        nuevaPelicula->setClasificacion(fields[3]);  // Asigna la clasificación
        nuevaPelicula->setSinopsis(fields[4]);  // Asigna la sinopsis
        nuevaPelicula->setDia(QDate::fromString(fields[5], "yyyy-MM-dd"));  // Asigna la fecha

        // Leer los horarios
        QStringList horarios = fields[6].split(";");  // Los horarios están separados por punto y coma
        QList<QTime> listaHorarios;  // Lista para almacenar los horarios
        for (const QString &hora : horarios) {  // Itera sobre los horarios
            QTime horario = QTime::fromString(hora, "HH:mm");  // Convierte el horario a QTime
            if(horario.isValid()) {  // Si el horario es válido
                listaHorarios.append(horario);  // Lo agrega a la lista
            } else {
                qDebug() << "Horario invalido ignorado: " << hora;  // Mensaje de depuración si el horario es inválido
            }
        }
        nuevaPelicula->setHorarios(listaHorarios);  // Asigna los horarios a la película

        vectorPelicula.push_back(nuevaPelicula);  // Agrega la película al vector
    }

    file.close();  // Cierra el archivo
    qDebug() << "Películas cargadas correctamente desde el archivo.";  // Mensaje de depuración
}

// Función para agregar una película
void Peliculas::agregarPelicula() {
    Peliculas* nuevaPelicula = new Peliculas(vectorPelicula);  // Crea una nueva película

    nuevaPelicula->setTitulo(ui->lineEdit_nombre->text().trimmed());  // Asigna el título desde la interfaz
    nuevaPelicula->setDuracion(ui->spinBox_duracion->value());  // Asigna la duración desde la interfaz
    nuevaPelicula->setGenero(ui->lineEdit_genero->text().trimmed());  // Asigna el género desde la interfaz
    nuevaPelicula->setClasificacion(ui->lineEdit_clasificacion->text().trimmed());  // Asigna la clasificación
    nuevaPelicula->setSinopsis(ui->textEdit_sinopsis->toPlainText().trimmed());  // Asigna la sinopsis
    nuevaPelicula->setDia(ui->dateEdit->date());  // Asigna la fecha desde la interfaz

    QList<QTime> horarios;  // Lista para almacenar los horarios
    if (ui->timeEdit->time().isValid()) horarios.append(ui->timeEdit->time());  // Agrega el primer horario si es válido
    if (ui->timeEdit_2->time().isValid()) horarios.append(ui->timeEdit_2->time());  // Agrega el segundo horario si es válido
    if (ui->timeEdit_3->time().isValid()) horarios.append(ui->timeEdit_3->time());  // Agrega el tercer horario si es válido
    if (ui->timeEdit_4->time().isValid()) horarios.append(ui->timeEdit_4->time());  // Agrega el cuarto horario si es válido

    if (horarios.isEmpty()) {  // Verifica si no se ingresaron horarios válidos
        QMessageBox::warning(this, "Error", "Debe ingresar al menos un horario válido.");  // Muestra un mensaje de error
        return;
    }

    nuevaPelicula->setHorarios(horarios);  // Asigna los horarios a la nueva película
    vectorPelicula.push_back(nuevaPelicula);  // Agrega la película al vector

    guardarPeliculasEnCSV(archivoCSV);  // Guarda las películas en el archivo CSV

    QMessageBox::information(this, "Éxito", "Película agregada correctamente.");  // Mensaje de éxito
}

// Función para buscar una película por título
void Peliculas::buscarPelicula() {
    QString valor = ui->lineEdit_nombre->text();  // Obtiene el texto de búsqueda

    if (valor.isEmpty()) {  // Verifica si el campo está vacío
        qDebug() << "El campo de búsqueda está vacío.";  // Mensaje de depuración
        return;
    }

    for (Peliculas* pelicula : vectorPelicula) {  // Itera sobre las películas
        if (pelicula->getTitulo().contains(valor, Qt::CaseInsensitive)) {  // Si encuentra la película
            qDebug() << "Película encontrada: " << pelicula->getTitulo();  // Mensaje de depuración
            ui->lineEdit_genero->setText(pelicula->getGenero());  // Rellena los campos con los datos de la película encontrada
            ui->lineEdit_clasificacion->setText(pelicula->getClasificacion());
            ui->textEdit_sinopsis->setPlainText(pelicula->getSinopsis());
            ui->spinBox_duracion->setValue(pelicula->getDuracion());
            ui->dateEdit->setDate(pelicula->getDia());
            break;
        }
    }
}

// Función para eliminar una película
void Peliculas::eliminarPelicula() {
    QString tituloEliminar = ui->lineEdit_buscar->text().trimmed();  // Obtiene el título a eliminar

    if (tituloEliminar.isEmpty()) {  // Verifica si el campo está vacío
        QMessageBox::warning(this, "Advertencia", "Por favor ingrese un título para eliminar.");  // Muestra un mensaje de advertencia
        return;
    }

    bool encontrada = false;  // Variable para verificar si se encontró la película
    for (auto it = vectorPelicula.begin(); it != vectorPelicula.end(); ++it) {  // Itera sobre el vector de películas
        if ((*it)->getTitulo().compare(tituloEliminar, Qt::CaseInsensitive) == 0) {  // Si encuentra el título
            delete *it;  // Elimina el objeto de memoria
            vectorPelicula.erase(it);  // Elimina la película del vector
            encontrada = true;  // Marca que la película fue encontrada
            break;
        }
    }

    if (encontrada) {  // Si la película fue encontrada
        guardarPeliculasEnCSV(archivoCSV);  // Guarda los cambios en el archivo CSV
        QMessageBox::information(this, "Éxito", "Película eliminada correctamente.");  // Mensaje de éxito
        ui->lineEdit_buscar->clear();  // Limpia el campo de búsqueda
    } else {
        QMessageBox::information(this, "No encontrada", "No se encontró una película con ese título.");  // Mensaje si no se encuentra la película
    }
}
