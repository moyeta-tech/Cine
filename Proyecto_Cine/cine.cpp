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

    this->setWindowIcon((QIcon(":/images/src/icons/image cine.ico")) );

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    //Conectamos el menu a los slots correspondientes
    connect(ui->actionRegistro_peliculas, &QAction::triggered, this, &Cine::agregarPelicula);
    connect (ui->actionVer_peliculas, &QAction::triggered, this, &Cine::mostrarPeliculas);

    connect (ui->actionRegistrar_clientes, &QAction::triggered, this, &Cine::agregarClientes);
    connect (ui->actionVer_clientes, &QAction::triggered, this, &Cine::mostrarClientes);

    connect (ui->actionRegistrar_personal, &QAction::triggered, this, &Cine::agregarEmpleados);
    connect (ui->actionVer_personal, &QAction::triggered, this, &Cine::mostrarEmpelados);



    connect (ui->actionVer_historial, &QAction::triggered, this, &Cine::mostrarHistorial);

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
        delete p;  // Elimina el objeto al que apunta 'p'
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

    VerPeliculas dialog(vectorPelicula,this);
    dialog.setWindowTitle("Tabla de peliculas");

    // LLAMAMOS AL METODO PARA ACTUALIZAR LA TABLA
    dialog.actualizaPeliculasTabla(vectorPelicula);

    // MUESTRA LA TABLA DE PELICULAS ACTUALIZADA
    dialog.exec();
}

void Cine::agregarClientes()
{
    Clientes *dialog = new Clientes(this->vectorClientes, this);
    connect(dialog, &Clientes::clienteAgregado, this, &Cine::procesarClienteAgregado);

    dialog->exec();
}

void Cine::mostrarClientes()
{
    VerClientes dialog(vectorClientes, this);

    // LLAMAMOS AL METODO PARA ACTUALIZAR LA TABLA CON LOS DATOS CARGADOS
    dialog.actualizarTablaClientes(vectorClientes);

    dialog.exec();
}

void Cine::agregarEmpleados()
{
    Empleados *dialog = new Empleados(this->vectorEmpleados, this);
    connect(dialog, &Empleados::empleadoAgregado, this, &Cine::procesarEmpleadoAgregado);
    dialog->exec();
}

void Cine::mostrarEmpelados()
{
    Empleados gestorEmpleados(this->vectorEmpleados, this);
    gestorEmpleados.leerEmpleadosDesdeArchivo();

    VerEmpleados dialog(this->vectorEmpleados, this);

    // LLAMAMOS AL METODO PARA INCLUIR Y ACTUALIZAR LOS DATOS A TABLA
    dialog.actualizarTablaEmpleados(this->vectorEmpleados);

    dialog.exec();
}

void Cine::mostrarHistorial(){

    verHistorial *ventanaHistorial = new verHistorial(vectorPago, vectorHistorial, this);

    ventanaHistorial->exec();

 }


void Cine::mostrarPrecios()
{
    Precios dialog(" ", 0.0f, 0.0f);
    dialog.exec();
}

void Cine::mostrarHorarios()
{
    Horarios dialog(vectorPelicula, this);
    dialog.exec();

}


void Cine::ventaBoletos()
{

    // Asignar valores correctos a las variables
    QString fecha = "2024-11-11";
    int cantAsientos = 5;

    // Crear el cliente, horario y pago con los parámetros necesarios
    Clientes cliente(vectorClientes, this);
    Horarios horario(vectorPelicula, this);  // Ahora pasamos los parámetros requeridos

    QString metodo = "Tarjeta";
    float monto = 100.0;
    QString fechaPago = "2024-11-11";
    Pago pago(metodo, monto, fechaPago, this);  // Se pasan los parámetros requeridos

    // Crear la ventana de Venta
    Venta ventaDialog(vectorPelicula,fecha, cantAsientos, &cliente, &horario, &pago, this);

    connect(&ventaDialog, &Venta::ventaConfirmada, this ,&Cine::agregarVenta);
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

void Cine::procesarClienteAgregado(int idcliente, QString nombre, QString apellido, int dni, int edad, int telefono){
    Clientes *nuevoCliente = new Clientes(vectorClientes, this);

    nuevoCliente->setIDcliente(idcliente);
    nuevoCliente->setNombre(nombre);
    nuevoCliente->setApellido(apellido);
    nuevoCliente->setDni(dni);
    nuevoCliente->setEdad(edad);
    nuevoCliente->setTelefono(telefono);

}

void Cine::procesarEmpleadoAgregado(int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto){
    Empleados *nuevoEmpleado = new Empleados(vectorEmpleados, this);

    nuevoEmpleado->setIDempleado(idempleado);
    nuevoEmpleado->setNombre(nombre);
    nuevoEmpleado->setApellido(apellido);
    nuevoEmpleado->setDni(dni);
    nuevoEmpleado->setEdad(edad);
    nuevoEmpleado->setTelefono(telefono);
    nuevoEmpleado->setPuesto(puesto);
}

void Cine::agregarVenta(QString fecha, double monto){

    Pago *nuevoPago = new Pago();
    nuevoPago->setMonto(monto);

    Venta *nuevaVenta = new Venta();
    nuevaVenta->setFecha(fecha);
    nuevaVenta->setPago(nuevoPago);

    vectorHistorial.push_back(nuevaVenta);
    vectorPago.push_back(nuevoPago);

}

