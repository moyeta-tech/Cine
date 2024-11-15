#ifndef VERCLIENTES_H
#define VERCLIENTES_H

#include <QDialog>
#include <QFile>
#include "clientes.h"
#include "QMessageBox"

namespace Ui {
class VerClientes;
}

class VerClientes : public QDialog
{
    Q_OBJECT

public:
    explicit VerClientes(std::vector<Clientes*> &vectorClientesRef, QWidget *parent = nullptr);
    ~VerClientes();

    // METODO PARA ACTUALIZAR LA TABLA DE CLIENTES
    void actualizarTablaClientes(std::vector<Clientes*> &vectorClientes);

private slots:
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

    void on_Boton_cerrar_clicked();

    void on_pushButton_clicked();

private:
    Ui::VerClientes *ui;
    std::vector<Clientes*> &vectorClientes;
};

#endif // VERCLIENTES_H
