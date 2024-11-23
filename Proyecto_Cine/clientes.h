#ifndef CLIENTES_H
#define CLIENTES_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QSpinBox>
#include <vector>

namespace Ui {
class Clientes;
}

class Clientes : public QDialog
{
    Q_OBJECT

public:
    explicit Clientes(std::vector<Clientes*> &vectorClientesRef, QWidget *parent = nullptr);
    ~Clientes();

    // Getters y Setters
    int getIDcliente() const;
    void setIDcliente(int idcliente);
    QString getNombre() const;
    void setNombre(const QString &nombre);
    QString getApellido() const;
    void setApellido(const QString &apellido);
    int getDni() const;
    void setDni(int dni);
    int getEdad() const;
    void setEdad(int edad);
    int getTelefono() const;
    void setTelefono(int telefono);

public slots:
    void registrarCliente();
    void leerClientesDesdeArchivo();

signals:
    void clienteAgregado(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono);

private:
    void initstylesheet();
    void guardarClienteEnCSV(const QString &archivo, const Clientes &cliente);
    void inicializarCSV(const QString &archivo);

    Ui::Clientes *ui;
    std::vector<Clientes*> &vectorClientes;

    int idCliente;
    QString Nombre;
    QString Apellido;
    int Dni;
    int Edad;
    int Telefono;
};

#endif // CLIENTES_H
