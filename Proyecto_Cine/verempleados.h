#ifndef VEREMPLEADOS_H
#define VEREMPLEADOS_H

#include <QDialog>
#include <QFile>

namespace Ui {
class VerEmpleados;
}

class VerEmpleados : public QDialog
{
    Q_OBJECT

public:
    explicit VerEmpleados(QWidget *parent = nullptr);
    ~VerEmpleados();

private slots:
    void mostrarEmpleado();
    void cerrarVentana();
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::VerEmpleados *ui;
};

#endif // VEREMPLEADOS_H
