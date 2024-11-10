#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include <QDialog>

namespace Ui {
class Empleados;
}

class Empleados : public QDialog
{
    Q_OBJECT

public:
    explicit Empleados(QWidget *parent = nullptr);
    ~Empleados();

    /*
    Empleado(string nombre, string apellido, int dni, int edad, int telefono, int idempleado);
    int getIDempleado();
    void setIDempleado(int idempleado);
    string getPuesto();
    void setPuesto(string puesto);

*/

private:
    Ui::Empleados *ui;
/*
    int idEmpleado;
    string Puesto;
*/

};

#endif // EMPLEADOS_H
