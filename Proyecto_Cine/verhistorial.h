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
    explicit verHistorial(std::vector<Venta* > &vectorHistorialRef, QWidget *parent = nullptr);
    ~verHistorial();

    void cargarDatosTabla(const QString &fecha, double monto);

private slots:
    void initstylesheet();

private:
    Ui::verHistorial *ui;
    std::vector<Venta* > &vectorHistorial;
};

#endif // VERHISTORIAL_H
