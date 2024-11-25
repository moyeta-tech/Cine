#ifndef PAGO_H
#define PAGO_H

#include <QDialog>
#include <QFile>

namespace Ui {
class Pago;
}

class Pago : public QDialog
{
    Q_OBJECT

public:
    explicit Pago(QString metodo, float monto, QString fecha,QWidget *parent = nullptr);
    ~Pago();

    Pago();
    QString getMetodo();
    void setMetodo(QString metodo);
    double getMonto() const;
    void setMonto(double monto);
    QString getFecha();
    void setFecha(QString fecha);

    void setAsientos(const QString& asientos); // Nuevo método para pasar asientos

    bool finalizarCompra();

private slots:

    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::Pago *ui;

    QString Metodo;
    double Monto;
    QString Fecha;

    QString AsientosSeleccionados; // Variable para almacenar los asientos

};

#endif // PAGO_H
