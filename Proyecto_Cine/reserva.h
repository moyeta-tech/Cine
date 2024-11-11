#ifndef RESERVA_H
#define RESERVA_H
#include "clientes.h"
#include "horarios.h"
#include "pagos.h"

#include <QDialog>

namespace Ui {
class reserva;
}

class reserva : public QDialog
{
    Q_OBJECT

public:
    explicit reserva(QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, pagos *pago, QWidget *parent = nullptr);
    ~reserva();
    QString getFecha();
    void setFecha(QString fecha);
    int getcantAsientos();
    void setcantAsientos(int cantasientos);

    Clientes *getCliente();
    void setCliente(Clientes *cliente);
    Horarios *getHorario();
    void setHorario(Horarios *horario);
    pagos *getPago();
    void setPago(pagos *pago);



private:
    Ui::reserva *ui;
    QString Fecha;
    int cantAsientos;
    Clientes *cliente;
    Horarios *horario;
    pagos *pago;

};

#endif // RESERVA_H

