#ifndef VENTA_H //Verifica si el archivo no ha sido incluido previamente
#define VENTA_H //Define VENTA_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QFile> //Incluimos la biblioteca para manejar operaciones de archivos
#include <QMessageBox> //Incluimos la biblioteca las cajas de mensaje para mostrar alertas y notificaciones

#include "clientes.h" //Incluimos la clase `Clientes` que se usa para manejar datos de los clientes
#include "horarios.h" //Incluimos la clase `Horarios` que maneja los horarios de las funciones
#include "pago.h" //Incluimos la clase `Pago` que gestiona los pagos realizados

namespace Ui {
class Venta;
}

class Venta : public QDialog
{
    Q_OBJECT

public:
    explicit Venta(std::vector<Peliculas *> VectorPeliculasRef, QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, Pago *pago, QWidget *parent = nullptr); //Constructor con parámetros para inicializar datos de la venta
    ~Venta();

    Venta(); // Constructor por defecto

    QString getFecha() const; // Obtiene la fecha de la venta
    void setFecha(QString fecha); // Establece la fecha de la venta

    int getcantAsientos(); // Obtiene la cantidad de asientos seleccionados
    void setcantAsientos(int cantasientos); // Establece la cantidad de asientos seleccionados

    Clientes *getCliente(); // Obtiene el cliente asociado a la venta
    void setCliente(Clientes *cliente); // Establece el cliente para la venta

    Horarios *getHorario(); // Obtiene el horario seleccionado para la película
    void setHorario(Horarios *horario); // Establece el horario para la venta

    Pago *getPago(); // Obtiene el objeto de pago asociado
    void setPago(Pago *pago); // Establece el objeto de pago

private slots:
    void initstylesheet(); // Slot para inicializar y cargar la hoja de estilo (CSS) para la interfaz

    void actualizarCosto(); // Actualiza el costo total de la venta
    void actualizarHorarios(); // Actualiza los horarios disponibles para las funciones

    void seleccionAsientos(); // Método para gestionar la selección de asientos por el cliente

    void aplicarDescuento10(); // Aplica un descuento del 10%
    void aplicarDescuento25(); // Aplica un descuento del 25%
    void aplicarDescuento2x1(); // Aplica el descuento 2x1 (dos entradas por el precio de una)

    void resetearDescuento(); // Resetea cualquier descuento aplicado

    void on_Boton_continuar_clicked(); // Evento que maneja el botón de continuar en la venta


signals:
    void ventaConfirmada(const QString &fecha, double monto); // Señal para confirmar la venta con la fecha y el monto total

private:
    Ui::Venta *ui; //Puntero a la interfaz gráfica generada automáticamente

    QString Fecha; //Almacena la fecha de la venta
    int cantAsientos; //Almacena la cantidad de asientos seleccionados
    Clientes *cliente; //Puntero al cliente asociado con la venta
    Horarios *horario; //Puntero al horario seleccionado para la película
    Pago *pago; //Puntero al objeto de pago para esta venta

    double costoTotal = 0.0; //Costo total de la venta, calculado después de aplicar los descuentos
    QString descuentoActivo = ""; //Almacena el tipo de descuento activo (si hay alguno)
    double costoBase = 0; //Precio base sin ningún descuento aplicado
    bool descuentoAplicado = false; //Indica si se ha aplicado un descuento

    //Referencia al vector de películas disponible para la venta
    std::vector<Peliculas *> VectorPeliculas;
};

#endif // VENTA_H
