#ifndef PAGO_H
#define PAGO_H

#include <QDialog>

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
    void on_Boton_finalizar_clicked();

private:
    Ui::Pago *ui;

    QString Metodo;
    float Monto;
    QString Fecha;

};

#endif // PAGO_H
