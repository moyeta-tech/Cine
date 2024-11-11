
#ifndef PAGOS_H
#define PAGOS_H

#include <QWidget>

namespace Ui {
class pagos;
}

class pagos : public QWidget
{
    Q_OBJECT

public:
    explicit pagos(QString metodo, float monto, QString fecha, QWidget *parent = nullptr);
    ~pagos();

    QString getMetodo();
    void setMetodo(QString metodo);
    float getMonto();
    void setMonto(float monto);
    QString getFecha();
    void setFecha(QString fecha);

private:
    Ui::pagos *ui;
    QString Metodo;
    float Monto;
    QString Fecha;
};

#endif // PAGOS_H

