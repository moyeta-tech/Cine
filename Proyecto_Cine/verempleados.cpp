#include "verempleados.h"
#include "ui_verempleados.h"

VerEmpleados::VerEmpleados(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerEmpleados)
{
    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Tabla de empleados");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // CONFIGURAMOS LA TABLA VERCLIENTES PARA 6 COLUMNAS
      ui->tableWidget->setColumnCount(6);

    // DECLARAMOS QSTRINGLIST PARA LAS COLUMNAS

    QStringList encabezados;

    encabezados << "IDempleado" << "Nombre" << "Apellido" << "Dni" << "Edad" << "Telefono";

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);

    //Conectamos los botones
    connect(ui->Boton_mostrar, &QPushButton::clicked, this, &VerEmpleados::mostrarEmpleado);
    connect(ui->Boton_cerrar, &QPushButton::clicked, this, &VerEmpleados::cerrarVentana);

}

VerEmpleados::~VerEmpleados()
{
    delete ui;
}

void VerEmpleados::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

void VerEmpleados::mostrarEmpleado()
{

}

void VerEmpleados::cerrarVentana()
{

}
