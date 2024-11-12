#ifndef PRECIOS_H
#define PRECIOS_H

#include <QDialog>

namespace Ui {
class Precios;
}

class Precios : public QDialog
{
    Q_OBJECT

public:
    explicit Precios(QString tipoentrada, float preciobase, float descuento, QDialog *parent = nullptr);

    ~Precios();

    QString getTipoEntrada();
    void setTipoEntrada(QString tipoentrada);
    float getprecioBase();
    void setprecioBase(float preciobase);
    float getDescuento();
    void setDescuento(float descuento);
    float calcularPrecio();


private:
    Ui::Precios *ui;

    QString TipoEntrada;
    float PrecioBase;
    float Descuento;
};

#endif // PRECIOS_H
