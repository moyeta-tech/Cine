#ifndef ASIENTOS_H
#define ASIENTOS_H

#include <QDialog>

namespace Ui {
class Asientos;
}

class Asientos : public QDialog
{
    Q_OBJECT

public:
    explicit Asientos(QWidget *parent = nullptr);
    Asientos(int numero, bool estado);

    ~Asientos();

    int getNumero();
    void setNumero(int numero);
    QString getFila();
    void setFila(QString fila);
    bool isOcupado();
    void setOcupado(bool ocupado);

private slots:
    void continuarPago();

    void on_Boton_continuar_clicked();

private:
    Ui::Asientos *ui;

    int Numero;
    bool Ocupado;
    QString Fila;

};

#endif // ASIENTOS_H
