#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include <QDialog>
#include <QFile>

namespace Ui {
class Empleados;
}

class Empleados : public QDialog
{
    Q_OBJECT

public:
    explicit Empleados(std::vector<Empleados* > &vectorEmpleadosRef, QWidget *parent = nullptr);
    ~Empleados();


    Empleados (int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto);
    int getIDempleado();
    void setIDempleado(int idempleado);

    QString getNombre();
    void setNombre(QString nombre);

    QString getApellido();
    void setApellido(QString apellido);

    int getDni();
    void setDni(int dni);

    int getEdad();
    void setEdad(int edad);

    int getTelefono();
    void setTelefono(int telefono);

    QString getPuesto();
    void setPuesto(QString puesto);

private slots:
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

    void on_buttonBox_accepted();

signals:
    void empleadoAgregado(int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto);

private:
    Ui::Empleados *ui;
    int idEmpleado;
    QString Nombre;
    QString Apellido;
    int Dni;
    int Edad;
    int Telefono;
    QString Puesto;

    std::vector<Empleados* > &vectorEmpleados;


};

#endif // EMPLEADOS_H
