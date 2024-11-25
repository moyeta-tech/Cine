#ifndef CINE_H //Verifica si CINE_H no ha sido definido previamente
#define CINE_H //Define CINE_H para evitar múltiples inclusiones del archivo

#include <QMainWindow> //Incluimos las bibliotecas necesarias para una ventana principal en Qt

#include <QDebug> //Incluimos la biblioteca que permite depuración mediante mensajes en la consola
#include <QMenuBar> //Incluimos la biblioteca que proporciona una barra de menú para la interfaz
#include <QAction> //Incluimos la biblioteca permite manejar acciones en el menú y la interfaz
#include <QMessageBox> //Incluimos la biblioteca que permite mostrar cuadros de mensaje
#include <QFile> //Incluimos la biblioteca que proporciona manejo de archivos

#include "clientes.h" //Incluimos la clase `Clientes`
#include "empleados.h" //Incluimos la clase `Empleados`
#include "peliculas.h" //Incluimos la clase `Peliculas`
#include "verhistorial.h" //Incluimos la clase `verHistorial`

namespace Ui {
class Cine;
}

class Cine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cine(QWidget *parent = nullptr);
    ~Cine();

    QString getNombre(); //Metodo para obtener el nombre del cine
    void setNombre(QString nombre); //Metodo para establecer el nombre del cine
    QString getUbicacion(); //Metodo para obtener la ubicación del cine
    void setUbicacion(QString ubicacion); //Metodo para establecer la ubicación del cine

private slots:
    void agregarPelicula(); //Slot para agregar una película
    void mostrarPeliculas(); //Slot para mostrar las películas

    void agregarClientes(); //Slot para agregar un cliente
    void mostrarClientes(); //Slot para mostrar los clientes

    void agregarEmpleados(); //Slot para agregar un empleado
    void mostrarEmpelados(); //Slot para mostrar los empleados

    void mostrarHistorial(); //Slot para mostrar el historial de ventas

    void mostrarPrecios(); //Slot para mostrar los precios de boletos
    void mostrarHorarios(); //Slot para mostrar los horarios disponibles

    void ventaBoletos(); //Slot para gestionar la venta de boletos

    void procesarPeliAgregada(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis); //Slot para procesar la adición de una película

    void procesarClienteAgregado(int idcliente, QString nombre, QString apellido, int dni, int edad, int telefono); //Slot para procesar la adición de un cliente

    void procesarEmpleadoAgregado(int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto); //Slot para procesar la adición de un empleado

    void agregarVenta(QString fecha, double monto); //Slot para agregar una venta al historial

    void initstylesheet(); //Slot para inicializar y cargar una hoja de estilo CSS

private:
    Ui::Cine *ui; //Puntero a la interfaz gráfica generada automáticamente

    QString Nombre; //Variable que almacena el nombre del cine
    QString Ubicacion; //Variable que almacena la ubicación del cine
    verHistorial *historialventana = nullptr; //Puntero a la ventana de historial de ventas

    std::vector<Peliculas*> vectorPelicula; //Contenedor para almacenar películas
    std::vector<Clientes*> vectorClientes; //Contenedor para almacenar clientes
    std::vector<Empleados*> vectorEmpleados; //Contenedor para almacenar empleados
    std::vector<Venta*> vectorHistorial; //Contenedor para almacenar el historial de ventas
    std::vector<Pago*> vectorPago; //Contenedor para almacenar pagos
};

#endif // CINE_H
