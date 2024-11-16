#include "verpeliculas.h"
#include "ui_verpeliculas.h"

VerPeliculas::VerPeliculas(std::vector<Peliculas *> &vectorPeliculaRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerPeliculas)
    , vectorPelicula(vectorPeliculaRef)
{
    ui->setupUi(this);

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    connect(ui->Boton_cerrar, &QPushButton::clicked, this, &VerPeliculas::cerrarVentana);

    // CONFIGURAMOS LA TABLA VERCLIENTES PARA 5 COLUMNAS
    ui->tableWidget->setColumnCount(5);

    // DECLARAMOS QSTRINGLIST PARA LAS COLUMNAS

    QStringList encabezados;

    encabezados << "Titulo" << "Duracion" << "Genero" << "Clasificacion" << "Sinopsis";

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);
}

VerPeliculas::~VerPeliculas()
{
    delete ui;
}

void VerPeliculas::actualizaPeliculasTabla(std::vector<Peliculas *> &vectorPelicula)
{

    ui->tableWidget->setRowCount(vectorPelicula.size());

    for(int i = 0; i < vectorPelicula.size(); i++)
    {
        const Peliculas *peli = vectorPelicula[i]; // Accede a cada elemento como referencia
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(peli->getTitulo()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(peli->getDuracion())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(peli->getGenero()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(peli->getClasificacion()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(peli->getSinopsis()));
    }
}

void VerPeliculas::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

void VerPeliculas::cerrarVentana()
{
    accept();
}

