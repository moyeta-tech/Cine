#ifndef VERCLIENTES_H // Verifica si el archivo no ha sido incluido previamente
#define VERCLIENTES_H // Define VERCLIENTES_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QFile> // Clase para manejar operaciones de archivos
#include <QTableWidget> // Clase para mostrar tablas en la interfaz gráfica
#include <vector> // Para usar la clase `std::vector` para manejar colecciones de clientes

#include "clientes.h" // Incluye la clase `Clientes`, que maneja la información de los clientes


namespace Ui {
class VerClientes;
}

class VerClientes : public QDialog
{
    Q_OBJECT

public:
    explicit VerClientes(const std::vector<Clientes*> &vectorClientesRef, QWidget *parent = nullptr); // Constructor con parámetros para inicializar los datos de los clientes
    ~VerClientes();

private slots:
    void initstylesheet(); //Slot para inicializar y cargar la hoja de estilo (CSS) para la interfaz
    void cargarClientes(); //Slot para cargar la información de los clientes en la interfaz
    void cargarClientesDesdeCSV(const QString &archivo); //Slot para cargar los clientes desde un archivo CSV


private:
    Ui::VerClientes *ui; //Puntero a la interfaz gráfica generada automáticamente

    std::vector<Clientes*> vectorClientes; //Referencia al vector de clientes

    void agregarClienteATabla(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono); // Método para agregar un cliente a la tabla visual

   };

#endif // VERCLIENTES_H
