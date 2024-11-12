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


    Empleados (QString nombre, QString apellido, int dni, int edad, int telefono, int idempleado);
    int getIDempleado();
    void setIDempleado(int idempleado);
    QString getPuesto();
    void setPuesto(QString puesto);



private:
    Ui::Empleados *ui;

    int idEmpleado;
    QString Puesto;


};

#endif // EMPLEADOS_H
