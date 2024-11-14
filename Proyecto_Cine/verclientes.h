#ifndef VERCLIENTES_H
#define VERCLIENTES_H

#include <QDialog>
#include <QFile>

namespace Ui {
class VerClientes;
}

class VerClientes : public QDialog
{
    Q_OBJECT

public:
    explicit VerClientes(QWidget *parent = nullptr);
    ~VerClientes();

private slots:
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::VerClientes *ui;
};

#endif // VERCLIENTES_H
