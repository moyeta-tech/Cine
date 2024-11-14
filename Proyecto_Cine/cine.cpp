#include "cine.h"
#include "ui_cine.h"

#include <QDebug>

#include "clientes.h"
#include "empleados.h"
#include "precios.h"
#include "horarios.h"
#include "venta.h"
#include "pago.h"
#include "verclientes.h"
#include "verempleados.h"
#include "verpeliculas.h"


Cine::Cine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cine)
{

    qDebug() << "Iniciando Cine";
    ui->setupUi(this);
    qDebug() << "Interfaz de usuario cargada";

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Inicio");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    //Conectamos el menu a los slots correspondientes
    connect(ui->actionRegistro_peliculas, &QAction::triggered, this, &Cine::agregarPelicula);
    connect (ui->actionVer_peliculas, &QAction::triggered, this, &Cine::mostrarPeliculas);

    connect (ui->actionRegistrar_clientes, &QAction::triggered, this, &Cine::agregarClientes);
    connect (ui->actionVer_clientes, &QAction::triggered, this, &Cine::mostrarClientes);

    connect (ui->actionRegistrar_personal, &QAction::triggered, this, &Cine::agregarEmpleados);
    connect (ui->actionVer_personal, &QAction::triggered, this, &Cine::mostrarEmpelados);

    //Conetamos los botones a los slots correspondientes
    connect(ui->Boton_horario, &QPushButton::clicked, this, &Cine::mostrarHorarios);
    connect(ui->Boton_precio, &QPushButton::clicked, this, &Cine::mostrarPrecios);
    connect(ui->Boton_venta, &QPushButton::clicked, this, &Cine::ventaBoletos);

    //Establecemos los iconos
    ui->label->setPixmap(QPixmap(":/images/src/icons/cartel.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_2->setPixmap(QPixmap(":/images/src/icons/billete.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_3->setPixmap(QPixmap(":/images/src/icons/boleto.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

Cine::~Cine()
{
    qDebug() << "Destruyendo Cine...";
    delete ui;
    // Liberar la memoria de los objetos almacenados en el vector
    for (Peliculas* p : vectorPelicula)
    {
        delete p;  // Elimina el objeto al que apunta el puntero
    }
}

// HOJA DE ESTILOS
void Cine::initstylesheet()
{
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
    Peliculas *dialog = new Peliculas(this->vectorPelicula, this);
    connect(dialog, &Peliculas::peliAgregada, this, &Cine::procesarPeliAgregada);

    dialog->exec();
}
void Cine::mostrarPeliculas()
{
    VerPeliculas dialog(this);
    dialog.exec();
}

void Cine::agregarClientes()
{
    Clientes dialog(vectorClientes, this);
    dialog.exec();
}

void Cine::mostrarClientes()
{
    VerClientes dialog(this);
    dialog.exec();
}

void Cine::agregarEmpleados()
{
    Empleados dialog(this);
    dialog.exec();
}

void Cine::mostrarEmpelados()
{
    VerEmpleados dialog(this);
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
    Clientes cliente(vectorClientes);  // Cliente se crea con su constructor sin parámetros
    QString hora = "12:00";
    QString dia = "Lunes";
    Horarios horario(hora, dia, this);  // Ahora pasamos los parámetros requeridos

    QString metodo = "Tarjeta";
    float monto = 100.0;
    QString fechaPago = "2024-11-11";
    Pago pago(metodo, monto, fechaPago, this);  // Se pasan los parámetros requeridos

    // Crear la ventana de Venta
    Venta ventaDialog(fecha, cantAsientos, &cliente, &horario, &pago, this);

    // Mostrar el diálogo
    ventaDialog.exec();
}

void Cine::procesarPeliAgregada(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis){
    Peliculas *nuevaPeli = new Peliculas(vectorPelicula, this);

    nuevaPeli->setTitulo(titulo);
    nuevaPeli->setDuracion(duracion);
    nuevaPeli->setGenero(genero);
    nuevaPeli->setClasificacion(clasificacion);
    nuevaPeli->setSinopsis(sinopsis);

}

void Cine::procesarClienteAgregado(string nombre, string apellido, int dni, int edad, int telefono, int idcliente){
    Clientes *nuevoCliente = new Clientes(vectorClientes, this);

    nuevoCliente->setIDcliente(idcliente);
    nuevoCliente->setNombre(nombre);
    nuevoCliente->setApellido(apellido);
    nuevoCliente->setDni(dni);
    nuevoCliente->setEdad(edad);
    nuevoCliente->setTelefono(telefono);

}


