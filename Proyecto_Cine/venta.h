#ifndef VENTA_H
#define VENTA_H

#include <QDialog>

#include "clientes.h"
#include "horarios.h"
#include "pago.h"

namespace Ui {
class Venta;
}

class Venta : public QDialog
{
    Q_OBJECT

public:
    explicit Venta(QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, Pago *pago, QWidget *parent = nullptr);
    ~Venta();

    QString getFecha();
    void setFecha(QString fecha);
    int getcantAsientos();
    void setcantAsientos(int cantasientos);

    Clientes *getCliente();
    void setCliente(Clientes *cliente);
    Horarios *getHorario();
    void setHorario(Horarios *horario);
    Pago *getPago();
    void setPago(Pago *pago);


private slots:
    void seleccionAsientos();


    void on_Boton_continuar_clicked();

private:
    Ui::Venta *ui;

    QString Fecha;
    int cantAsientos;
    Clientes *cliente;
    Horarios *horario;
    Pago *pago;

};

#endif // VENTA_H
