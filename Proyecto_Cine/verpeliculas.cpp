#include "verpeliculas.h"  // Incluir la definición de la clase VerPeliculas
#include "ui_verpeliculas.h"  // Incluir la interfaz de usuario generada por Qt
#include "peliculas.h"  // Incluir la definición de la clase Peliculas
#include <QFile>  // Incluir para manejar archivos
#include <QTextStream>  // Incluir para leer archivos de texto
#include <QMessageBox>  // Incluir para mostrar cuadros de mensaje
#include <QDebug>  // Incluir para la depuración
#include <QDir>  // Incluir para manejar directorios

VerPeliculas::VerPeliculas(std::vector<Peliculas*>& peliculas, QWidget *parent) :
    QDialog(parent),  // Constructor de la clase VerPeliculas, hereda de QDialog
    ui(new Ui::VerPeliculas),  // Inicializa la interfaz de usuario
    peliculas(peliculas)  // Inicializa el vector de películas
{
    ui->setupUi(this);  // Configura la interfaz de usuario desde el archivo .ui

    // Configurar el QTableWidget con 7 columnas
    ui->tableWidget->setColumnCount(7);  // Establece 7 columnas en la tabla
    ui->tableWidget->setHorizontalHeaderLabels({"Título", "Duración", "Género", "Clasificación", "Sinopsis", "Días", "Horas"});  // Asigna los encabezados de las columnas

    // Asegurarse de que la tabla sea visible
    ui->tableWidget->resizeColumnsToContents();  // Ajusta el tamaño de las columnas automáticamente
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Deshabilita la edición de celdas

    // Ruta del archivo CSV desde el directorio de ejecución
    QString rutaArchivo = QDir::currentPath() + "/peliculas.csv";  // Define la ruta del archivo CSV
    qDebug() << "Ruta para cargar archivo: " << rutaArchivo;  // Muestra la ruta del archivo en la consola

    // Cargar películas desde el archivo CSV
    // cargarPeliculasDesdeCSV(rutaArchivo);  // Llama a la función para cargar películas desde el archivo CSV (actualmente comentada)

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();  // Llama a la función para cargar el archivo de estilo
}

VerPeliculas::~VerPeliculas()  // Destructor de la clase VerPeliculas
{
    delete ui;  // Libera la memoria de la interfaz de usuario
}

void VerPeliculas::initstylesheet()  // Función para cargar y aplicar el estilo desde un archivo
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Abre el archivo de estilo
    bool styleOK = style.open(QFile::ReadOnly);  // Intenta abrir el archivo en modo solo lectura
    qDebug() << "Apertura de archivos: " << styleOK;  // Muestra si el archivo se abrió correctamente en la consola
    QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el contenido del archivo y lo convierte a QString
    this->setStyleSheet(stringEstilo);  // Aplica el estilo a la ventana
}

void VerPeliculas::cargarPeliculasDesdeCSV(const QString &archivo)  // Función para cargar las películas desde un archivo CSV
{
    QFile file(archivo);  // Abre el archivo CSV
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // Verifica que el archivo se abra correctamente
        qDebug() << "No se pudo abrir el archivo CSV para lectura en: " << archivo;  // Muestra un mensaje de error si el archivo no se pudo abrir
        return;
    }

    QTextStream stream(&file);  // Crea un flujo de texto para leer el archivo
    QString line;  // Variable para almacenar cada línea leída
    int lineCount = 0;  // Variable para contar las líneas leídas
    while (!stream.atEnd()) {  // Mientras haya más líneas para leer
        line = stream.readLine();  // Lee la línea
        lineCount++;  // Incrementa el contador de líneas
        QStringList campos = line.split(',');  // Separa la línea por comas

        // Asegúrate de que la línea tenga al menos 6 campos
        if (campos.size() >= 6) {  // Verifica que haya suficientes campos
            QString titulo = campos[0];  // El primer campo es el título
            int duracion = campos[1].toInt();  // El segundo campo es la duración
            QString genero = campos[2];  // El tercer campo es el género
            QString clasificacion = campos[3];  // El cuarto campo es la clasificación
            QString dias = campos[4];  // El quinto campo es "Días"
            QString horarios = campos.size() > 5 ? campos[5] : "";  // El sexto campo es "Horarios"
            QString sinopsis = campos.size() > 6 ? campos[6] : "Sinopsis no disponible";  // El séptimo campo es "Sinopsis"

            // Dividir horarios por tabuladores si están presentes
            QStringList horariosList = horarios.split('\t');  // Separa los horarios por tabuladores

            // Agregar película a la tabla con el valor de "Días"
            agregarPeliculaATabla(titulo, duracion, genero, clasificacion, dias, horariosList.join("; "), sinopsis);  // Llama a la función para agregar la película a la tabla

        } else {
            qDebug() << "Línea inválida en el archivo: " << line << " en la línea: " << lineCount;  // Muestra un mensaje de error si la línea es inválida
        }
    }

    file.close();  // Cierra el archivo
}

void VerPeliculas::agregarPeliculaATabla(const QString &titulo, int duracion, const QString &genero,
                                         const QString &clasificacion, const QString &dias, const QString &horarios,
                                         const QString &sinopsis)  // Función para agregar una película a la tabla
{
    qDebug() << "Agregando película: " << titulo << duracion << genero << clasificacion << dias << horarios << sinopsis;  // Muestra los detalles de la película que se va a agregar

    int row = ui->tableWidget->rowCount();  // Obtiene el número de filas actuales en la tabla
    ui->tableWidget->insertRow(row);  // Inserta una nueva fila en la tabla

    // Inserta los datos de la película en las columnas correspondientes
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(titulo));  // Inserta el título en la primera columna
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(duracion)));  // Inserta la duración en la segunda columna
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(genero));  // Inserta el género en la tercera columna
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(clasificacion));  // Inserta la clasificación en la cuarta columna
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(dias));  // Inserta "Días" en la quinta columna
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(horarios));  // Inserta los horarios en la sexta columna
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(sinopsis));  // Inserta la sinopsis en la séptima columna
}
