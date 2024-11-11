
#ifndef PRECIOS_H
#define PRECIOS_H

#include <QWidget>

namespace Ui {
class precios;
}

class precios : public QWidget
{
    Q_OBJECT

public:
    explicit precios(QString tipoentrada, float preciobase, float descuento, QWidget *parent = nullptr);
    ~precios();
    QString getTipoEntrada();
    void setTipoEntrada(QString tipoentrada);
    float getprecioBase();
    void setprecioBase(float preciobase);
    float getDescuento();
    void setDescuento(float descuento);
    float calcularPrecio();


private:
    Ui::precios *ui;
    QString TipoEntrada;
    float PrecioBase;
    float Descuento;
};

#endif // PRECIOS_H

