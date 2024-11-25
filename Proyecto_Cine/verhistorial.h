#ifndef VERHISTORIAL_H
#define VERHISTORIAL_H

#include <QDialog>
#include "QFile"
#include "QMessageBox"
#include "venta.h"
#include "pago.h"
#include "QDebug"
#include "vector"

namespace Ui {
class verHistorial;
}

class verHistorial : public QDialog
{
    Q_OBJECT

public:
    explicit verHistorial(std::vector<Pago* > &vectorPagoRef, std::vector<Venta* > &vectorHistorialRef, QWidget *parent = nullptr);
    ~verHistorial();
    void mostrarDatosHistorial();

private slots:
    void initstylesheet();

private:
    Ui::verHistorial *ui;
    std::vector<Venta* > &vectorHistorial;
    std::vector<Pago* > &vectorPago;
};

#endif // VERHISTORIAL_H
