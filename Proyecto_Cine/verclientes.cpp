#include "verclientes.h"
#include "ui_verclientes.h"

VerClientes::VerClientes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerClientes)
{
    ui->setupUi(this);

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // CONFIGURAMOS LA TABLA VERCLIENTES PARA 6 COLUMNAS
    ui->tableWidget->setColumnCount(6);

    // DECLARAMOS QSTRINGLIST PARA LAS COLUMNAS

    QStringList encabezados;

    encabezados << "IDcliente" << "Nombre" << "Apellido" << "Dni" << "Edad" << "Telefono";

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);
}

VerClientes::~VerClientes()
{
    delete ui;
}

void VerClientes::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
