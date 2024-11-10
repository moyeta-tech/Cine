#ifndef CLIENTES_H
#define CLIENTES_H

#include <QDialog>

namespace Ui {
class Clientes;
}

class Clientes : public QDialog
{
    Q_OBJECT

public:
    explicit Clientes(QWidget *parent = nullptr);
    ~Clientes();

    /*
    Clientes (string nombre, string apellido, int dni, int edad, int teléfono, int idCliente);
    int getIDcliente();
    void setIDcliente(int idcliente);
    void agregarHistorial(string reserva);
    // void getHistorial(historial);
    void mostrarHistorial();
*/

private:
    Ui::Clientes *ui;
/*
    int idCliente;
    std::vector<string> historial;
*/

};

#endif // CLIENTES_H
