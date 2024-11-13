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
#include "array"

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

    //Slots para los botones
    void mostrarPrecios();
    void mostrarHorarios();
    void ventaBoletos();

<<<<<<< HEAD
    // SLOT PARA AGREGAR UNA NUEVA PELICULA AL VECTOR
    void procesarPeliAgregada(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis);
=======
    void initstylesheet();
>>>>>>> 724aafccd9b8b8dfb3091b12d66cdb715f57cf92

private:
    Ui::Cine *ui;
    // ATRIBUTOS
    QString Nombre;
    QString Ubicacion;

    // CONTENEDORES PARA EL MANEJO DE DATOS

    std::vector<Peliculas*> vectorPelicula;
    std::map<int, Clientes> mapClientes;
    std::map<int, Empleados> mapEmpleados;
};

#endif // CINE_H
