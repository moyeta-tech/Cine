#ifndef CINE_H
#define CINE_H

#include <QMainWindow>

#include <array>
#include <QDebug>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QFile>

#include "clientes.h"
#include "empleados.h"
#include "peliculas.h"
#include "sala.h"
#include "map"
#include "unordered_map"

namespace Ui {
class Cine;
}

class Cine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cine(QWidget *parent = nullptr);
    ~Cine();

    // METODOS
    QString getNombre();
    void setNombre(QString nombre);
    QString getUbicacion();
    void setUbicacion(QString ubicacion);

private slots:
    //Slots para los elementos de QMenuBar
    void agregarPelicula();
    void agregarClientes();
    void agregarEmpleados();
    void mostrarEmpelados();

    //Slots para los botones
    void mostrarPrecios();
    void mostrarHorarios();
    void ventaBoletos();


    // SLOT PARA AGREGAR UNA NUEVA PELICULA AL VECTOR
    void procesarPeliAgregada(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis);

    // SLOT PARA AGREGAR UN CLIENTE AL MAPA
    void procesarClienteAgregado(string nombre, string apellido, int dni, int edad, int telefono, int idcliente);

    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();


private:
    Ui::Cine *ui;
    // ATRIBUTOS
    QString Nombre;
    QString Ubicacion;

    // CONTENEDORES PARA EL MANEJO DE DATOS

    std::vector<Peliculas*> vectorPelicula;
    std::vector<Clientes*> vectorClientes;
    std::map<int, Empleados> mapEmpleados;
};

#endif // CINE_H
