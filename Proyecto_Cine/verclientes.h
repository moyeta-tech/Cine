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
    void initstylesheet();
    void cargarClientes();
    void cargarClientesDesdeCSV(const QString &archivo);  // Nuevo método para cargar CSV

private:
    Ui::VerClientes *ui;
    std::vector<Clientes*> vectorClientes;

    void agregarClienteATabla(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono);  // Método para agregar clientes a la tabla
};

#endif // VERCLIENTES_H
