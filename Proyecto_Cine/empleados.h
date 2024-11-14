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
    explicit Empleados(QWidget *parent = nullptr);
    ~Empleados();


    Empleados (int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono);
    int getIDempleado();
    void setIDempleado(int idempleado);
    QString getPuesto();
    void setPuesto(QString puesto);

private slots:
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::Empleados *ui;

    int idEmpleado;
    QString Puesto;


};

#endif // EMPLEADOS_H
