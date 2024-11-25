#ifndef VERHISTORIAL_H // Verifica si el archivo no ha sido incluido previamente
#define VERHISTORIAL_H // Define VERHISTORIAL_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QFile> //Incluye la funcionalidad para manejar archivos
#include <QMessageBox> //Para mostrar mensajes emergentes en la interfaz de usuario
#include <QDebug> //Funciones de depuración para imprimir mensajes en la consola
#include <vector> //Utiliza la clase `std::vector` para manejar colecciones de datos

#include "venta.h" // Incluye la clase `Venta`, que maneja las transacciones de venta
#include "pago.h" // Incluye la clase `Pago`, que maneja los detalles de pago en una transacción


namespace Ui {
class verHistorial;
}

class verHistorial : public QDialog
{
    Q_OBJECT

public:
    explicit verHistorial(std::vector<Pago* > &vectorPagoRef, std::vector<Venta* > &vectorHistorialRef, QWidget *parent = nullptr); // Constructor que recibe referencias a vectores de `Pago` y `Venta`
    ~verHistorial();

    void mostrarDatosHistorial(); //Método para mostrar los datos del historial (ventas y pagos)

private slots:
    void initstylesheet(); //Slot para inicializar y cargar la hoja de estilo (CSS) para la interfaz

private:
    Ui::verHistorial *ui; // Puntero a la interfaz gráfica generada automáticamente

    std::vector<Venta* > &vectorHistorial; // Referencia al vector de objetos `Venta`, que almacena las transacciones
    std::vector<Pago* > &vectorPago; // Referencia al vector de objetos `Pago`, que almacena los detalles de pago

};

#endif // VERHISTORIAL_H
