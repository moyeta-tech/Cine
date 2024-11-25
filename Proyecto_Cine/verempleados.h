#ifndef VEREMPLEADOS_H //Verifica si el archivo no ha sido incluido previamente
#define VEREMPLEADOS_H //Define VEREMPLEADOS_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluye la clase base para cuadros de diálogo en Qt

#include <QTableWidget> // lase para mostrar tablas en la interfaz gráfica
#include <vector> //Para usar la clase `std::vector` para manejar colecciones de empleados

#include "empleados.h" //Incluye la clase `Empleados`, que maneja la información de los empleados

namespace Ui {
class VerEmpleados;
}

class VerEmpleados : public QDialog
{
    Q_OBJECT

public:
    explicit VerEmpleados(std::vector<Empleados*>& empleados, QWidget *parent = nullptr); // Constructor con parámetros para inicializar los datos de los empleados
    ~VerEmpleados();

private slots:
    void initstylesheet(); //Slot para inicializar y cargar la hoja de estilo (CSS) para la interfaz

private:
    Ui::VerEmpleados *ui; //Puntero a la interfaz gráfica generada automáticamente

    std::vector<Empleados*>& empleados; //Referencia al vector de empleados


    void cargarEmpleadosDesdeCSV(const QString &archivo); // Método para cargar los empleados desde un archivo CSV

    void agregarEmpleadoATabla(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono, const QString &puesto); //Método para agregar un empleado a la tabla visual

};

#endif // VEREMPLEADOS_H
