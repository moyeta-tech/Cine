#include "cine.h"
#include "ui_cine.h"

#include <QDebug>                    // Para el registro de depuración (logs).
#include "clientes.h"                // Incluye la clase 'Clientes' que maneja la información de los clientes.
#include "empleados.h"               // Incluye la clase 'Empleados' para manejar la información del personal.
#include "precios.h"                 // Incluye la clase 'Precios' para gestionar los precios de los boletos.
#include "horarios.h"                // Incluye la clase 'Horarios' para manejar los horarios de las funciones.
#include "venta.h"                   // Incluye la clase 'Venta' que maneja las transacciones de venta de boletos.
#include "pago.h"                    // Incluye la clase 'Pago' para manejar el proceso de pago.
#include "verclientes.h"             // Incluye la clase para mostrar la lista de clientes registrados.
#include "verempleados.h"            // Incluye la clase para mostrar la lista de empleados.
#include "verpeliculas.h"            // Incluye la clase para mostrar las películas registradas.
#include "asientos.h"                // Incluye la clase 'Asientos' para manejar la selección de asientos.


Cine::Cine(QWidget *parent)            // Constructor de la clase Cine.
    : QMainWindow(parent)               // Inicializa la clase base QMainWindow.
    , ui(new Ui::Cine)                  // Crea la interfaz de usuario asociada.
{
    qDebug() << "Iniciando Cine";       // Mensaje de depuración para iniciar la clase 'Cine'.
    ui->setupUi(this);                  // Configura la interfaz de usuario.
    qDebug() << "Interfaz de usuario cargada";  // Mensaje de depuración indicando que la interfaz se cargó.

    this->setWindowIcon(QIcon(":/images/src/icons/image cine.ico"));  // Establece el icono de la ventana.

    // Llamada al método para cargar la hoja de estilos (CSS)
    initstylesheet();

    // Conecta las acciones del menú con sus slots correspondientes.
    connect(ui->actionRegistro_peliculas, &QAction::triggered, this, &Cine::agregarPelicula);
    connect(ui->actionVer_peliculas, &QAction::triggered, this, &Cine::mostrarPeliculas);
    connect(ui->actionRegistrar_clientes, &QAction::triggered, this, &Cine::agregarClientes);
    connect(ui->actionVer_clientes, &QAction::triggered, this, &Cine::mostrarClientes);
    connect(ui->actionRegistrar_personal, &QAction::triggered, this, &Cine::agregarEmpleados);
    connect(ui->actionVer_personal, &QAction::triggered, this, &Cine::mostrarEmpelados);
    connect(ui->actionVer_historial, &QAction::triggered, this, &Cine::mostrarHistorial);

    // Conecta los botones a sus respectivos slots
    connect(ui->Boton_horario, &QPushButton::clicked, this, &Cine::mostrarHorarios);
    connect(ui->Boton_precio, &QPushButton::clicked, this, &Cine::mostrarPrecios);
    connect(ui->Boton_venta, &QPushButton::clicked, this, &Cine::ventaBoletos);

    // Establece iconos para algunos labels en la interfaz
    ui->label->setPixmap(QPixmap(":/images/src/icons/cartel.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_2->setPixmap(QPixmap(":/images/src/icons/billete.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_3->setPixmap(QPixmap(":/images/src/icons/boleto.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

Cine::~Cine()  // Destructor de la clase Cine.
{
    qDebug() << "Destruyendo Cine...";  // Mensaje de depuración cuando se destruye la clase.
    delete ui;  // Libera la memoria utilizada por la interfaz de usuario.

    // Libera la memoria de los objetos almacenados en el vector de películas.
    for (Peliculas* p : vectorPelicula)
    {
        delete p;  // Elimina cada objeto 'Peliculas' en el vector.
    }
}

// Carga el estilo desde un archivo CSS
void Cine::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet.css");  // Carga el archivo de estilos.
    bool styleOK = style.open(QFile::ReadOnly);  // Abre el archivo en modo lectura.
    qDebug() << "Apertura de archivos: " <<styleOK;  // Mensaje de depuración para verificar la apertura del archivo.
    QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el contenido del archivo.
    this->setStyleSheet(stringEstilo);  // Aplica el estilo a la interfaz.
}

// Métodos GET y SET para el nombre del cine
QString Cine::getNombre()
{
    return Nombre;  // Devuelve el nombre del cine.
}

void Cine::setNombre(QString nombre)
{
    Nombre = nombre;  // Establece el nombre del cine.
}

// Métodos GET y SET para la ubicación del cine
QString Cine::getUbicacion()
{
    return Ubicacion;  // Devuelve la ubicación del cine.
}

void Cine::setUbicacion(QString ubicacion)
{
    Ubicacion = ubicacion;  // Establece la ubicación del cine.
}

// Método para agregar una película
void Cine::agregarPelicula()
{
    Peliculas *dialog = new Peliculas(this->vectorPelicula, this);  // Crea un objeto 'Peliculas' para agregar una nueva película.
    connect(dialog, &Peliculas::peliAgregada, this, &Cine::procesarPeliAgregada);  // Conecta la señal 'peliAgregada' al método 'procesarPeliAgregada'.
    dialog->exec();  // Muestra el diálogo de agregar película.
}

// Método para mostrar las películas registradas
void Cine::mostrarPeliculas()
{
    Peliculas cargarPeli(vectorPelicula, this);  // Crea un objeto 'Peliculas' para cargar las películas desde el CSV.
    cargarPeli.cargarPeliculasDesdeCSV("peliculas.csv");  // Carga las películas desde el archivo CSV.

    VerPeliculas dialog(vectorPelicula,this);  // Crea el diálogo para mostrar las películas.
    dialog.cargarPeliculasDesdeCSV("peliculas.csv");  // Carga las películas desde el archivo.
    dialog.exec();  // Muestra el diálogo de las películas.
}

// Método para agregar un cliente
void Cine::agregarClientes()
{
    Clientes *dialog = new Clientes(this->vectorClientes, this);  // Crea el objeto de clientes para agregar un nuevo cliente.
    connect(dialog, &Clientes::clienteAgregado, this, &Cine::procesarClienteAgregado);  // Conecta la señal de cliente agregado.
    dialog->exec();  // Muestra el diálogo de agregar cliente.
}

// Método para mostrar los clientes registrados
void Cine::mostrarClientes()
{
    std::vector<Clientes*> vectorClientes;  // Declara el vector de clientes.
    VerClientes dialog(vectorClientes, this);  // Crea el diálogo para ver los clientes.
    dialog.exec();  // Muestra el diálogo de clientes.
}

// Método para agregar un empleado
void Cine::agregarEmpleados()
{
    Empleados *dialog = new Empleados(this->vectorEmpleados, this);  // Crea el objeto de empleados para agregar un nuevo empleado.
    dialog->exec();  // Muestra el diálogo de agregar empleado.
}

// Método para mostrar los empleados registrados
void Cine::mostrarEmpelados()
{
    VerEmpleados *verEmpleadosDialog = new VerEmpleados(vectorEmpleados, this);  // Crea el diálogo para ver los empleados.
    verEmpleadosDialog->exec();  // Muestra el diálogo de empleados.
}

// Método para mostrar el historial de ventas y pagos
void Cine::mostrarHistorial()
{
    verHistorial *ventanaHistorial = new verHistorial(vectorPago, vectorHistorial, this);  // Crea el objeto para ver el historial de pagos.
    ventanaHistorial->mostrarDatosHistorial();  // Muestra los datos del historial.
    ventanaHistorial->exec();  // Muestra el diálogo del historial.
}

// Método para mostrar los precios de los boletos
void Cine::mostrarPrecios()
{
    Precios dialog(" ", 0.0f, 0.0f);  // Crea el diálogo de precios.
    dialog.exec();  // Muestra el diálogo de precios.
}

// Método para mostrar los horarios de las películas
void Cine::mostrarHorarios()
{
    Horarios dialog(vectorPelicula, this);  // Crea el diálogo de horarios.
    dialog.exec();  // Muestra el diálogo de horarios.
}

// Método para realizar la venta de boletos
void Cine::ventaBoletos()
{
    QString fecha = "2024-11-11";  // Asigna la fecha de la venta.
    int cantAsientos = 5;         // Asigna la cantidad de asientos seleccionados.

    // Crear objetos necesarios para la venta
    Clientes cliente(vectorClientes, this);
    Horarios horario(vectorPelicula, this);
    QString metodo = "Tarjeta";  // Método de pago.
    float monto = 100.0;  // Monto de la venta.
    QString fechaPago = "2024-11-11";  // Fecha del pago.
    Pago pago(metodo, monto, fechaPago, this);  // Crea el objeto de pago.

    // Crea el diálogo de venta de boletos
    Venta ventaDialog(vectorPelicula, fecha, cantAsientos, &cliente, &horario, &pago, this);

    connect(&ventaDialog, &Venta::ventaConfirmada, this, &Cine::agregarVenta);  // Conecta la señal de venta confirmada.

    ventaDialog.exec();  // Muestra el diálogo de venta de boletos.
}

// Métodos de procesamiento de información agregada (películas, clientes, empleados)
void Cine::procesarPeliAgregada(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis)
{
    Peliculas *nuevaPeli = new Peliculas(vectorPelicula, this);
    nuevaPeli->setTitulo(titulo);
    nuevaPeli->setDuracion(duracion);
    nuevaPeli->setGenero(genero);
    nuevaPeli->setClasificacion(clasificacion);
    nuevaPeli->setSinopsis(sinopsis);
}

void Cine::procesarClienteAgregado(int idcliente, QString nombre, QString apellido, int dni, int edad, int telefono)
{
    Clientes *nuevoCliente = new Clientes(vectorClientes, this);
    nuevoCliente->setIDcliente(idcliente);
    nuevoCliente->setNombre(nombre);
    nuevoCliente->setApellido(apellido);
    nuevoCliente->setDni(dni);
    nuevoCliente->setEdad(edad);
    nuevoCliente->setTelefono(telefono);
}

void Cine::procesarEmpleadoAgregado(int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto)
{
    Empleados *nuevoEmpleado = new Empleados(vectorEmpleados, this);
    nuevoEmpleado->setIDempleado(idempleado);
    nuevoEmpleado->setNombre(nombre);
    nuevoEmpleado->setApellido(apellido);
    nuevoEmpleado->setDni(dni);
    nuevoEmpleado->setEdad(edad);
    nuevoEmpleado->setTelefono(telefono);
    nuevoEmpleado->setPuesto(puesto);
}

void Cine::agregarVenta(QString fecha, double monto)
{
    Pago *nuevoPago = new Pago();
    nuevoPago->setMonto(monto);

    Venta *nuevaVenta = new Venta();
    nuevaVenta->setFecha(fecha);
    nuevaVenta->setPago(nuevoPago);

    vectorHistorial.push_back(nuevaVenta);  // Agrega la nueva venta al historial.
    vectorPago.push_back(nuevoPago);  // Agrega el nuevo pago a la lista de pagos.
}
