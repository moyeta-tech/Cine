#ifndef VENTA_H
#define VENTA_H

#include <QDialog>
#include <QFile>
#include <QRadioButton>
#include <QSpinBox>
#include <QMessageBox>

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

    // Método para aplicar descuento
    void aplicarDesc();

private slots:
    // Inicialización del stylesheet
    void initstylesheet();

    // Métodos para actualizar costos y horarios
    void actualizarCosto();
    void actualizarHorarios();

    // Método para gestionar la selección de asientos
    void seleccionAsientos();

private:
    Ui::Venta *ui;

    // Atributos
    QString Fecha;
    int cantAsientos;
    Clientes *cliente;
    Horarios *horario;
    Pago *pago;

    // Atributos de la venta
    double costoTotal = 0.0;
    QString descuentoActivo = "";

    // Referencia al vector de películas
    std::vector<Peliculas *> &VectorPeliculas;
};

#endif // VENTA_H
