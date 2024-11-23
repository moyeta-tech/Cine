#ifndef VERCLIENTES_H
#define VERCLIENTES_H

#include <QDialog>
#include <QFile>
#include <QTableWidget>
#include <vector>
#include "clientes.h"

namespace Ui {
class VerClientes;
}

class VerClientes : public QDialog
{
    Q_OBJECT

public:
    explicit VerClientes(const std::vector<Clientes*> &vectorClientesRef, QWidget *parent = nullptr);
    ~VerClientes();

private slots:
    // Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();
    // Slot para cargar la información de los clientes en la tabla
    void cargarClientes();

private:
    Ui::VerClientes *ui;
    const std::vector<Clientes*> &vectorClientes;
};

#endif // VERCLIENTES_H
