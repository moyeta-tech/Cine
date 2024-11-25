#ifndef VENTA_H
#define VENTA_H

#include <QDialog>
#include <QFile>
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
    explicit Venta(std::vector<Peliculas *> VectorPeliculasRef, QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, Pago *pago, QWidget *parent = nullptr);
    ~Venta();

    Venta();
    QString getFecha() const;
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
    // Inicialización del stylesheet
    void initstylesheet();

    // Métodos para actualizar costos y horarios
    void actualizarCosto();
    void actualizarHorarios();

    // Método para gestionar la selección de asientos
    void seleccionAsientos();

    // Métodos para aplicar descuentos
    void aplicarDescuento10(); // Aplicar descuento del 10%
    void aplicarDescuento25(); // Aplicar descuento del 25%
    void aplicarDescuento2x1(); // Aplicar descuento 2x1

    void resetearDescuento();

    void on_Boton_continuar_clicked();

public slots:

signals:
    void ventaConfirmada(const QString &fecha, double monto);

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
    double costoBase = 0;  // Almacena el precio base sin descuentos
    bool descuentoAplicado = false; // Para saber si ya se ha aplicado un descuento

    // Referencia al vector de películas
    std::vector<Peliculas *> VectorPeliculas;
};

#endif // VENTA_H
