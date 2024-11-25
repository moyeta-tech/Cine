#ifndef PRECIOS_H //Verifica si el archivo no ha sido incluido previamente
#define PRECIOS_H //Define PRECIOS_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo
#include <QFile> //Incluimos la biblioteca para manejar operaciones de archivos

namespace Ui {
class Precios;
}

class Precios : public QDialog
{
    Q_OBJECT

public:
    explicit Precios(QString tipoentrada, float preciobase, float descuento, QDialog *parent = nullptr); //Constructor con parámetros para inicializar tipo, precio base y descuento
    ~Precios();

    QString getTipoEntrada(); //Obtenemos el tipo de entrada
    void setTipoEntrada(QString tipoentrada); //Establecemos el tipo de entrada

    float getprecioBase(); //Obtenemos el precio base
    void setprecioBase(float preciobase); //Establecemos el precio base

    float getDescuento(); //Obtenemos el descuento aplicado
    void setDescuento(float descuento); //Establemcemos el descuento

    float calcularPrecio(); //Metodo para calcula el precio final después del descuento

private slots:
    void initstylesheet(); // lot para inicializar y aplicar la hoja de estilos (CSS)

private:
    Ui::Precios *ui; //Puntero a la interfaz gráfica generada automáticamente

    QString TipoEntrada; //Almacena el tipo de entrada (ej. general, VIP)
    float PrecioBase; //Almacena el precio base de la entrada
    float Descuento; //Almacena el descuento aplicado a la entrada
};

#endif // PRECIOS_H
