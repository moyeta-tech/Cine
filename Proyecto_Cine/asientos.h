#ifndef ASIENTOS_H
#define ASIENTOS_H

#include <QWidget>

namespace Ui {
class asientos;
}

class asientos : public QWidget
{
    Q_OBJECT

public:
    explicit asientos(QWidget *parent = nullptr);
    asientos(int numero, bool estado);
    ~asientos();
    int getNumero();
    void setNumero(int numero);
    QString getFila();
    void setFila(QString fila);
    bool isOcupado();
    void setOcupado(bool ocupado);

private:
    Ui::asientos *ui;
    int Numero;
    bool Ocupado;
    QString Fila;
};

#endif // ASIENTOS_H
