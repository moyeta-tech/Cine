#ifndef INICIOSESION_H
#define INICIOSESION_H

#include <QDialog>
#include <QFile>
#include <QSet>  // Para almacenar los IDs de los empleados
#include <QDebug>

namespace Ui {
class InicioSesion;
}

class InicioSesion : public QDialog
{
    Q_OBJECT

public:
    explicit InicioSesion(QWidget *parent = nullptr);
    ~InicioSesion();

private slots:
    void iniciarSesion();
    void salirVentana();

    // Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::InicioSesion *ui;

    // Función que valida si el ID de empleado existe en el conjunto de empleados
    bool validarCredenciales(const QString &usuario);

    // Conjunto estático para almacenar los IDs de los empleados
    static QSet<QString> empleadosIDs;

    // Carga los IDs de los empleados desde el archivo CSV
    void cargarEmpleados();
};

#endif // INICIOSESION_H
