#ifndef ASIENTOS_H
#define ASIENTOS_H

#include <QDialog>

#include <QFile>

namespace Ui {
class Asientos;
}

class Asientos : public QDialog
{
    Q_OBJECT

public:
    explicit Asientos(QWidget *parent = nullptr);
    Asientos(int numero, bool estado);

    ~Asientos();

    int getNumero();
    void setNumero(int numero);
    QString getFila();
    void setFila(QString fila);
    bool isOcupado();
    void setOcupado(bool ocupado);

private slots:
    void continuarPago();

    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

    void seleccionarAsiento(); // Slot para manejar la selección de un asiento
    void actualizarAsientoOcupado(int indice); // Actualiza un asiento a ocupado

private:
    Ui::Asientos *ui;

    int Numero;
    bool Ocupado;
    QString Fila;

    // Lista para almacenar los botones de los asientos
    QList<QPushButton*> botonesAsientos;

    // Lista para almacenar los asientos ocupados (por su índice)
    QList<int> asientosOcupados;

    // Función para inicializar y marcar los asientos ocupados
    void marcarAsientosOcupados();

    // Función para guardar los asientos ocupados en un archivo
    void guardarAsientosOcupados();

    // Función para cargar los asientos ocupados desde un archivo
    void cargarAsientosOcupados();

};

#endif // ASIENTOS_H
