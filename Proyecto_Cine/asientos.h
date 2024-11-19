#ifndef ASIENTOS_H
#define ASIENTOS_H

#include <QDialog>

#include <QFile>
#include <QStringList>
#include <QMessageBox>

namespace Ui {
class Asientos;
}

class Asientos : public QDialog
{
    Q_OBJECT

public:
    explicit Asientos(QWidget *parent = nullptr);
    ~Asientos();

    int getNumero();
    void setNumero(int numero);
    QString getFila();
    void setFila(QString fila);

    // Método para obtener la lista de asientos seleccionados
    QStringList getAsientosSeleccionados() const;

    // Método para establecer el límite de asientos seleccionables
    void setLimiteAsientos(int limite);

private slots:
    void continuarPago();  // Slot para continuar al pago

    // Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

    void seleccionarAsiento(); // Slot para manejar la selección de un asiento
    void actualizarAsientoOcupado(int indice); // Actualiza un asiento a ocupado

private:
    Ui::Asientos *ui;

    int Numero;        // Número del asiento
    bool Ocupado;      // Estado de ocupación del asiento
    QString Fila;      // Fila del asiento

    // Lista para almacenar los botones de los asientos
    QList<QPushButton*> botonesAsientos;

    // Lista para almacenar los asientos ocupados (por su índice)
    QList<int> asientosOcupados;

    // Lista de asientos seleccionados (cuando el usuario los selecciona)
    QStringList asientosSeleccionados;

    // Función para inicializar y marcar los asientos ocupados
    void marcarAsientosOcupados();

    // Función para guardar los asientos ocupados en un archivo
    void guardarAsientosOcupados();

    // Función para cargar los asientos ocupados desde un archivo
    void cargarAsientosOcupados();

    // Límite de asientos seleccionables
    int limiteAsientos = 0;

    // Número de asientos actualmente seleccionados
    int seleccionados = 0;
};

#endif // ASIENTOS_H
