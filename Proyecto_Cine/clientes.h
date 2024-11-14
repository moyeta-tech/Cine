#ifndef CLIENTES_H
#define CLIENTES_H

#include <QDialog>
#include <vector>
#include <QFile>
#include "QDebug"

using namespace std;

namespace Ui {
class Clientes;
}

class Clientes : public QDialog
{
    Q_OBJECT

public:
    explicit Clientes(std::vector<Clientes*> &vectorClientesRef, QWidget *parent = nullptr);
    ~Clientes();


    Clientes (string nombre, string apellido, int dni, int edad, int telefono, int idcliente);
    string getNombre();
    void setNombre(string nombre);
    int getIDcliente();
    void setIDcliente(int idcliente);
    string getApellido();
    void setApellido(string apellido);
    int getDni();
    void setDni(int dni);
    int getEdad();
    void setEdad(int edad);
    int getTelefono();
    void setTelefono(int telefono);

    std::vector<QString> getHistorial();
 //   void agregarHistorial(reserva *Reserva);
    void mostrarHistorial();

private slots:
    void initstylesheet();

    void on_buttonBox_accepted();


signals:
    void clienteAgregado(int idcliente, string nombre, string apellido, int dni,
                         int edad, int telefono);
private:
    Ui::Clientes *ui;


    string Nombre;
    string Apellido;
    int Dni;
    int Edad;
    int Telefono;
    int idCliente;
    std::vector<QString> Historial;
    std::vector<Clientes*> &vectorClientes;
//    reserva *Reserva;

};

#endif // CLIENTES_H
