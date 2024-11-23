#ifndef VEREMPLEADOS_H
#define VEREMPLEADOS_H

#include <QDialog>
#include <QTableWidget>
#include <vector>
#include "empleados.h"

namespace Ui {
class VerEmpleados;
}

class VerEmpleados : public QDialog
{
    Q_OBJECT

public:
    explicit VerEmpleados(std::vector<Empleados*>& empleados, QWidget *parent = nullptr);
    ~VerEmpleados();

private:
    Ui::VerEmpleados *ui;
    std::vector<Empleados*>& empleados;

    // Declarar funciones
    void cargarEmpleadosDesdeCSV(const QString &archivo);
    void agregarEmpleadoATabla(int id, const QString &nombre, const QString &apellido,
                               int dni, int edad, int telefono, const QString &puesto);
};

#endif // VEREMPLEADOS_H
