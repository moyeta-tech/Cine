#ifndef VEREMPLEADOS_H
#define VEREMPLEADOS_H

#include <QDialog>
#include <QFile>
#include "empleados.h"
#include "QMessageBox"
#include "QStringList"

namespace Ui {
class VerEmpleados;
}

class VerEmpleados : public QDialog
{
    Q_OBJECT

public:
    explicit VerEmpleados(std::vector<Empleados* > &vectorEmpleadosRef, QWidget *parent = nullptr);
    ~VerEmpleados();

    // METODO PARA ACTUALIZAR TABLA Y CARGARLA
    void actualizarTablaEmpleados(std::vector<Empleados* > &vectorEmpleados);

private slots:
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

    void cerrarVentana();

    void eliminarEmpleado();



private:
    Ui::VerEmpleados *ui;
    std::vector<Empleados* > &vectorEmpleados;
    QStringList lineasLeidas;
};

#endif // VEREMPLEADOS_H
