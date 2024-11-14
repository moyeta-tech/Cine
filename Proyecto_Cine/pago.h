#ifndef PAGO_H
#define PAGO_H

#include <QDialog>
#include <QFile>

namespace Ui {
class Pago;
}

class Pago : public QDialog
{
    Q_OBJECT

public:
    explicit Pago(QString metodo, float monto, QString fecha,QWidget *parent = nullptr);
    ~Pago();

    QString getMetodo();
    void setMetodo(QString metodo);
    float getMonto();
    void setMonto(float monto);
    QString getFecha();
    void setFecha(QString fecha);


private slots:
    void finalizarCompra();

    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::Pago *ui;

    QString Metodo;
    float Monto;
    QString Fecha;

};

#endif // PAGO_H
