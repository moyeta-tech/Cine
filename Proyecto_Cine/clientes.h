#ifndef CLIENTES_H //Verifica si CLIENTES_H no ha sido definido previamente
#define CLIENTES_H //Define CLIENTES_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QString> //Incluimos la biblioteca para manejar cadenas de texto en Qt
#include <QFile> //Incluimos la biblioteca para trabajar con archivos
#include <QTextStream> //Incluimos la biblioteca para manejar flujos de texto
#include <QMessageBox> //Incluimos la biblioteca para cuadros de mensaje
#include <QDir> //Incluimos la biblioteca para manejar directorios
#include <QSpinBox> //Incluimos la biblioteca para entrada numérica con botones incrementales
#include <vector> //Incluimos la biblioteca estándar para el manejo de vectores

namespace Ui {
class Clientes;
}

class Clientes : public QDialog
{
    Q_OBJECT

public:
    explicit Clientes(std::vector<Clientes*> &vectorClientesRef, QWidget *parent = nullptr); // Constructor que toma un vector de clientes como referencia y un padre opcional
    ~Clientes();

    int getIDcliente() const; //Obtenemos el ID del cliente
    void setIDcliente(int idcliente); //Establecemos el ID del cliente

    QString getNombre() const; //Obtenemos el nombre del cliente
    void setNombre(const QString &nombre); //Establecemos el nombre del cliente

    QString getApellido() const; //Obtenemos el apellido del cliente
    void setApellido(const QString &apellido); //Establecemos el apellido del cliente

    int getDni() const; // Obtenemos el DNI del cliente
    void setDni(int dni); //Establecemos el DNI del cliente

    int getEdad() const; // Obtenemos la edad del cliente
    void setEdad(int edad); //Establecemos la edad del cliente

    int getTelefono() const; // Obtenemos el número de teléfono del cliente
    void setTelefono(int telefono); //Establecemos el número de teléfono del cliente

public slots:
    void registrarCliente(); //Slot para registrar un cliente

    void leerClientesDesdeArchivo(); //Slot para leer clientes desde un archivo

signals:
    void clienteAgregado(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono); //Señal emitida cuando se agrega un cliente

private:
    Ui::Clientes *ui; //Puntero a la interfaz gráfica generada automáticamente

    void initstylesheet(); //Metodo para inicializar y cargar una hoja de estilo (CSS)

    void guardarClienteEnCSV(const QString &archivo, const Clientes &cliente); //Metodo para guardar un cliente en un archivo CSV

    void inicializarCSV(const QString &archivo); //Metodo para inicializar un archivo CSV si no existe

    std::vector<Clientes*> &vectorClientes; //Referencia al vector que almacena los clientes

    int idCliente; //Variable que almacena el ID único del cliente
    QString Nombre; //Variable que almacena el nombre del cliente
    QString Apellido; //Variable que almacena el apellido del cliente
    int Dni; //Variable que almacena el DNI del cliente
    int Edad; //Variable que almacena la edad del cliente
    int Telefono; //Variable que almacena el numero de teléfono del cliente
};

#endif // CLIENTES_H
