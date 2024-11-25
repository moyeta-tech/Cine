#ifndef PAGO_H //Verifica si PAGO_H no ha sido definido previamente
#define PAGO_H //Define PAGO_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QFile> //Incluimos la biblioteca para manejar archivos en Qt


namespace Ui {
class Pago;
}

class Pago : public QDialog
{
    Q_OBJECT

public:
    explicit Pago(QString metodo, float monto, QString fecha, QWidget *parent = nullptr); // Constructor que inicializa un pago con método, monto y fecha
    ~Pago();

    Pago(); //Constructor por defecto

    QString getMetodo(); //Metodo getter para obtener el método de pago
    void setMetodo(QString metodo); //Metodo setter para establecer el método de pago

    double getMonto() const; //Metodo getter para obtener el monto de pago
    void setMonto(double monto); //Metodo setter para establecer el monto de pago

    QString getFecha(); //Metodo getter para obtener la fecha del pago
    void setFecha(QString fecha); //Metodo setter para establecer la fecha del pago

    void setAsientos(const QString& asientos); //Metodo para asignar los asientos seleccionados

    bool finalizarCompra(); //Metodo para finalizar la compra

private slots:
    void initstylesheet(); //Slot para inicializar y cargar la hoja de estilo (CSS)

private:
    Ui::Pago *ui; //Puntero a la interfaz gráfica generada automáticamente

    QString Metodo; //Variable para almacenar el método de pago
    double Monto; //Variable para almacenar el monto del pago
    QString Fecha; //Variable para almacenar la fecha del pago

    QString AsientosSeleccionados; //Variable para almacenar los asientos seleccionados
};

#endif // PAGO_H
