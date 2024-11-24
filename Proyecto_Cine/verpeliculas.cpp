#include "verpeliculas.h"
#include "ui_verpeliculas.h"
#include "peliculas.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QDir>

VerPeliculas::VerPeliculas(std::vector<Peliculas*>& peliculas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerPeliculas),
    peliculas(peliculas)
{
    ui->setupUi(this);

    // Configurar el QTableWidget con 7 columnas
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({"Título", "Duración", "Género", "Clasificación", "Días", "Horarios", "Sinopsis"});

    // Asegúrate de que la tabla sea visible
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Evitar edición

    // Ruta del archivo CSV desde el directorio de ejecución
    QString rutaArchivo = QDir::currentPath() + "/peliculas.csv";
    qDebug() << "Ruta para cargar archivo: " << rutaArchivo;

    // Cargar películas desde el archivo CSV
    cargarPeliculasDesdeCSV(rutaArchivo);

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();
}

VerPeliculas::~VerPeliculas()
{
    delete ui;
}

void VerPeliculas::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " << styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

void VerPeliculas::cargarPeliculasDesdeCSV(const QString &archivo)
{
    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo CSV para lectura en: " << archivo;
        return;
    }

    QTextStream stream(&file);
    QString line;
    int lineCount = 0;
    while (!stream.atEnd()) {
        line = stream.readLine();
        lineCount++;
        QStringList campos = line.split(',');

        // Asegúrate de que la línea tenga al menos 6 campos
        if (campos.size() >= 6) {
            QString titulo = campos[0];  // El primer campo es el título
            int duracion = campos[1].toInt();  // El segundo campo es la duración
            QString genero = campos[2];  // El tercer campo es el género
            QString clasificacion = campos[3];  // El cuarto campo es la clasificación
            QString fecha = campos[4];  // El quinto campo es la fecha
            QString dias = campos[5];  // El sexto campo es "Días"
            QString horarios = campos.size() > 6 ? campos[6] : "";  // El séptimo campo es "Horarios"
            QString sinopsis = campos.size() > 7 ? campos[7] : "Sinopsis no disponible";  // El octavo campo es "Sinopsis"

            // Dividir horarios por tabuladores si están presentes
            QStringList horariosList = horarios.split('\t');

            // Agregar película a la tabla con el valor de "Días"
            agregarPeliculaATabla(titulo, duracion, genero, clasificacion, dias, horariosList.join("; "), sinopsis);

        } else {
            qDebug() << "Línea inválida en el archivo: " << line << " en la línea: " << lineCount;
        }
    }

    file.close();
}

void VerPeliculas::agregarPeliculaATabla(const QString &titulo, int duracion, const QString &genero,
                                         const QString &clasificacion, const QString &dias, const QString &horarios,
                                         const QString &sinopsis)
{
    qDebug() << "Agregando película: " << titulo << duracion << genero << clasificacion << dias << horarios << sinopsis;

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(titulo));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(duracion)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(genero));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(clasificacion));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(dias));  // Insertar "Días"
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(horarios));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(sinopsis));
}
