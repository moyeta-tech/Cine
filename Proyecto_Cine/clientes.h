#ifndef CLIENTES_H
#define CLIENTES_H

#include <QDialog>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

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

    // Métodos para manejo de datos
    static void guardarClienteEnCSV(const QString &archivo, const Clientes &cliente);
    static void inicializarCSV(const QString &archivo);
    void leerClientesDesdeArchivo();

private slots:
    void initstylesheet(); // Inicializa la hoja de estilo
    void registrarCliente(); // Registra un nuevo cliente

signals:
    void clienteAgregado(int idcliente, QString nombre, QString apellido, int dni, int edad, int telefono);

private:
    Ui::Clientes *ui;

    // Atributos del cliente
    int idCliente;
    QString Nombre;
    QString Apellido;
    int Dni;
    int Edad;
    int Telefono;

    // Referencia al vector global de clientes
    std::vector<Clientes*> &vectorClientes;
};

#endif // CLIENTES_H
