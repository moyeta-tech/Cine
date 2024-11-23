#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include <QDialog>
#include <QFile>
#include <QString>
#include <vector>

namespace Ui {
class Empleados;
}

class Empleados : public QDialog
{
    Q_OBJECT

public:
    explicit Empleados(std::vector<Empleados*> &vectorEmpleadosRef, QWidget *parent = nullptr);
    ~Empleados();

    // Getters y Setters
    int getIDempleado() const;
    void setIDempleado(int idempleado);
    QString getNombre() const;
    void setNombre(const QString &nombre);
    QString getApellido() const;
    void setApellido(const QString &apellido);
    int getDni() const;
    void setDni(int dni);
    int getEdad() const;
    void setEdad(int edad);
    int getTelefono() const;
    void setTelefono(int telefono);
    QString getPuesto() const;
    void setPuesto(const QString &puesto);

public slots:
    void leerEmpleadosDesdeArchivo(); // Leer empleados desde un archivo CSV
    void registrarEmpleado();         // Registrar un nuevo empleado y guardarlo en el CSV

private slots:
    void initstylesheet(); // Inicializar hoja de estilos para el widget

signals:
    void empleadoAgregado(int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto);

private:
    Ui::Empleados *ui;

    // Atributos del empleado
    int idEmpleado;
    QString Nombre;
    QString Apellido;
    int Dni;
    int Edad;
    int Telefono;
    QString Puesto;

    // Referencia al vector global de empleados
    std::vector<Empleados*> &vectorEmpleados;
};

// Funciones auxiliares para manejo de CSV
void guardarEmpleadoEnCSV(const QString &archivo, const Empleados &empleado);
void inicializarCSV(const QString &archivo);

#endif // EMPLEADOS_H
