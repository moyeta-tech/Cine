#ifndef RESERVA_H
#define RESERVA_H
#include "cliente.h"
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
    explicit reserva(QString fecha, int cantasientos, Cliente *cliente, Horarios *horario, pagos *pago, QWidget *parent = nullptr);
    ~reserva();
    QString getFecha();
    void setFecha(QString fecha);
    int getcantAsientos();
    void setcantAsientos(int cantasientos);



private:
    Ui::reserva *ui;
    QString Fecha;
    int cantAsientos;
    Cliente *cliente;
    Horarios *horario;
    pagos *pago;

};

#endif // RESERVA_H
