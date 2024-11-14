#include "verpeliculas.h"
#include "ui_verpeliculas.h"

VerPeliculas::VerPeliculas(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerPeliculas)
{
    ui->setupUi(this);

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

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

void VerPeliculas::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
