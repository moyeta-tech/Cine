#ifndef VENTA_H
#define VENTA_H

#include <QDialog>

#include <QFile>

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
    explicit Venta(std::vector<Peliculas *> &VectorPeliculasRef, QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, Pago *pago, QWidget *parent = nullptr);
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

    // METODO PARA APLICAR DESCUENTO
    void aplicarDesc();


private slots:
    void seleccionAsientos();

    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

    // METODO PARA ACTUALIZAR COSTO
    void actualizarCosto();

private:
    Ui::Venta *ui;

    QString Fecha;
    int cantAsientos;
    Clientes *cliente;
    Horarios *horario;
    Pago *pago;
    // ATRIBUTOS PARA REALIZAR UNA VENTA
    double costoTotal = 0.0;
    QString descuentoActivo = "";

    std::vector<Peliculas *> &VectorPeliculas;

};

#endif // VENTA_H
