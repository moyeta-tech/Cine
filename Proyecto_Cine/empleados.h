#ifndef EMPLEADOS_H //Verifica si EMPLEADOS_H no ha sido definido previamente
#define EMPLEADOS_H //Define EMPLEADOS_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QFile> //Incluimos la biblioteca para manejo de archivos
#include <QString> //Incluimos la biblioteca para cadenas de texto en Qt
#include <vector> //Incluimos la biblioteca estándar para manejar vectores

namespace Ui {
class Empleados;
}

class Empleados : public QDialog
{
    Q_OBJECT

public:
    explicit Empleados(std::vector<Empleados*> &vectorEmpleadosRef, QWidget *parent = nullptr); // Constructor que inicializa el objeto y recibe una referencia al vector global de empleados
    ~Empleados();

    int getIDempleado() const; //Obtenemos el ID del empleado
    void setIDempleado(int idempleado); //Establecemos el ID del empleado

    QString getNombre() const; //Obtenemos el nombre del empleado
    void setNombre(const QString &nombre); //Establecemos el nombre del empleado

    QString getApellido() const; //Obtenemos el apellido del empleado
    void setApellido(const QString &apellido); //Establecemos el apellido del empleado

    int getDni() const; //Obtenemos el DNI del empleado
    void setDni(int dni); //Establecemos el DNI del empleado

    int getEdad() const; //Obtenemos la edad del empleado
    void setEdad(int edad); //Establecemos la edad del empleado

    int getTelefono() const; //Obtenemos el número de teléfono del empleado
    void setTelefono(int telefono); //Establecemos el número de teléfono del empleado

    QString getPuesto() const; //Obtenemos el puesto del empleado
    void setPuesto(const QString &puesto); //Establecemos el puesto del empleado

public slots:
    void leerEmpleadosDesdeArchivo(); //Slot para leer empleados desde un archivo CSV

    void registrarEmpleado(); //Slot para registrar un nuevo empleado y guardarlo en el archivo CSV

private slots:
    void initstylesheet(); //Slot para inicializar y cargar una hoja de estilo (CSS)


signals:
    void empleadoAgregado(int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto); //Señal emitida al agregar un empleado

private:
    Ui::Empleados *ui; //Puntero a la interfaz gráfica generada automáticamente

    int idEmpleado; //Variable que almacena el ID único del empleado
    QString Nombre; //Variable que almacena el nombre del empleado
    QString Apellido; //Variable que almacena el apellido del empleado
    int Dni; //Variable que almacena el DNI del empleado
    int Edad; //Variable que almacena la edad del empleado
    int Telefono; //Variable que almacena el número de teléfono del empleado
    QString Puesto; //Variable que almacena el puesto de trabajo del empleado

    std::vector<Empleados*> &vectorEmpleados; //Referencia al vector global que almacena los empleados

};

//Funciones auxiliares para manejo de archivos CSV
void guardarEmpleadoEnCSV(const QString &archivo, const Empleados &empleado); //Funcion para guardar un empleado en un archivo CSV

void inicializarCSV(const QString &archivo); //Funcion para inicializar un archivo CSV si no existe

#endif // EMPLEADOS_H
