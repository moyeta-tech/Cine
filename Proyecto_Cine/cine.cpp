#include "cine.h"
#include "ui_cine.h"

#include <QDebug>

#include "peliculas.h"
#include "clientes.h"
#include "empleados.h"
#include "precios.h"
#include "horarios.h"
#include "venta.h"
#include "pago.h"
#include "iniciosesion.h"


Cine::Cine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cine)
{

    qDebug() << "Iniciando Cine";
    ui->setupUi(this);
    qDebug() << "Interfaz de usuario cargada";

    //Titulo de la ventana
    this->setWindowTitle("Inicio");

    initstylesheet();

    //Conectamos el menu a los slots correspondientes
    connect(ui->actionRegistro_peliculas, &QAction::triggered, this, &Cine::agregarPelicula);
    connect (ui->actionRegistrar_clientes, &QAction::triggered, this, &Cine::agregarClientes);
    connect (ui->actionRegistrar_personal, &QAction::triggered, this, &Cine::agregarEmpleados);

    //Conetamos los botones a los slots correspondientes
    connect(ui->Boton_horario, &QPushButton::clicked, this, &Cine::mostrarHorarios);
    connect(ui->Boton_precio, &QPushButton::clicked, this, &Cine::mostrarPrecios);
    connect(ui->Boton_venta, &QPushButton::clicked, this, &Cine::ventaBoletos);

}

Cine::~Cine()
{
    qDebug() << "Destruyendo Cine..";
    delete ui;
}

// HOJA DE ESTILOS

void Cine::initstylesheet(){
    QFile style(":/src/stylesheet/stylesheet.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}


// GET Y SET DE NOMBRE

QString Cine::getNombre(){
    return Nombre;
}

 void Cine::setNombre(QString nombre){
     Nombre = nombre;
}

// GET Y SET DE UBICACION

QString Cine::getUbicacion(){
    return Ubicacion;
}

void Cine::setUbicacion(QString ubicacion){
    Ubicacion = ubicacion;
}


void Cine::agregarPelicula()
{
    Peliculas dialog("Nueva Película", 120, "Acción", "PG-13", "Sinopsis de la película", this);
    dialog.exec();
}

void Cine::agregarClientes()
{
    Clientes dialog(this);
    dialog.exec();

}

void Cine::agregarEmpleados()
{
    Empleados dialog(this);
    dialog.exec();
}


void Cine::mostrarPrecios()
{
    Precios dialog(" ", 0.0f, 0.0f);
    dialog.exec();
}

void Cine::mostrarHorarios()
{
    Horarios dialog(" ", " ");
    dialog.exec();

}


void Cine::ventaBoletos()
{
    // Asignar valores correctos a las variables
    QString fecha = "2024-11-11";
    int cantAsientos = 5;

    // Crear el cliente, horario y pago con los parámetros necesarios
    Clientes *cliente = new Clientes();  // Cliente se crea con su constructor sin parámetros
    QString hora = "12:00";
    QString dia = "Lunes";
    Horarios *horario = new Horarios(hora, dia, this);  // Ahora pasamos los parámetros requeridos

    QString metodo = "Tarjeta";
    float monto = 100.0;
    QString fechaPago = "2024-11-11";
    Pago *pago = new Pago(metodo, monto, fechaPago, this);  // Se pasan los parámetros requeridos

    // Crear la ventana de Venta
    Venta *ventaDialog = new Venta(fecha, cantAsientos, cliente, horario, pago, this);

    // Mostrar el diálogo
    ventaDialog->exec();
}




