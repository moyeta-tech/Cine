#ifndef INICIOSESION_H //Verifica si INICIOSESION_H no ha sido definido previamente
#define INICIOSESION_H //Define INICIOSESION_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QFile> //Incluimos la biblioteca para manejar archivos
#include <QSet> //Incluimos la biblioteca para conjuntos, utilizada para almacenar IDs de empleados
#include <QDebug> //Incluimos la biblioteca para las funciones de depuración para imprimir en la consola


namespace Ui {
class InicioSesion;
}

class InicioSesion : public QDialog
{
    Q_OBJECT

public:
    explicit InicioSesion(QWidget *parent = nullptr); // Constructor que inicializa el cuadro de diálogo con un padre opcional
    ~InicioSesion();

private slots:
    void iniciarSesion(); //Slot para manejar el evento de inicio de sesión

    void salirVentana(); //Slot para cerrar la ventana de inicio de sesión

    void initstylesheet(); //Slot para inicializar y cargar la hoja de estilo (CSS) del widget

private:
    Ui::InicioSesion *ui; //Puntero a la interfaz gráfica generada automáticamente

    bool validarCredenciales(const QString &usuario); //Validamos si el ID de empleado existe en el conjunto `empleadosIDs`

    static QSet<QString> empleadosIDs; //Conjunto estático para almacenar los IDs únicos de empleados

    void cargarEmpleados(); //Cargamos los IDs de los empleados desde un archivo CSV y los almacena en `empleadosIDs`

    QString obtenerNombreEmpleado(const QString &idEmpleado); //Obtenemos el nombre del empleado asociado a un ID desde el archivo CSV

};

#endif // INICIOSESION_H
