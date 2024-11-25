#ifndef ASIENTOS_H //Verifica si ASIENTOS_H no ha sido definido previamente
#define ASIENTOS_H //Define ASIENTOS_H para evitar multiples inclusiones de este archivo


#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QFile> //Incluimos bibliotecas para manejar archivos
#include <QStringList> //Incluimos bibliotecas para cadenas de texto
#include <QMessageBox> //Incluimos bibliotecas para cuadros de mensajes

namespace Ui {
class Asientos;
}

class Asientos : public QDialog
{
    Q_OBJECT

public:
    explicit Asientos(QWidget *parent = nullptr);
    ~Asientos();

    int getNumero(); //Metodo para obtener el numero de asiento

    void setNumero(int numero); //Metodo para establecer el numero de asiento

    QString getFila(); //Metodo para obtener la fila del asiento

    void setFila(QString fila); //Metodo para establecer la fila del asiento

    QStringList getAsientosSeleccionados() const; //Metodo para obtener la lista de asientos seleccionados por el usuario

    void setLimiteAsientos(int limite); //Metodo para establecer el limite de asientos seleccionables

private slots:
    void continuarPago(); //Slot para manejar la acción de continuar al pago

    void initstylesheet(); //Slot para inicializar y cargar la hoja de estilo (CSS) para personalizar el diseño

    void seleccionarAsiento(); //Slot para manejar la acción de seleccionar un asiento

    void actualizarAsientoOcupado(int indice); //Slot para marcar un asiento como ocupado según su índice

private:
    Ui::Asientos *ui; //Puntero a la interfaz gráfica generada automáticamente

    int Numero; // Variable que almacena el numero del asiento
    bool Ocupado; // Variable booleana que indica si el asiento esta ocupado
    QString Fila; // Variable que almacena la fila del asiento

    QList<QPushButton*> botonesAsientos; //Lista que contiene los botones correspondientes a los asientos en la interfaz

    QList<int> asientosOcupados; //Lista que almacena los índices de los asientos ocupados

    QStringList asientosSeleccionados; //Lista de cadenas que representan los asientos seleccionados por el usuario

    void marcarAsientosOcupados(); //Metodo para inicializar y marcar los asientos ocupados en la interfaz

    void guardarAsientosOcupados(); //Metodo para guardar los asientos ocupados en un archivo

    void cargarAsientosOcupados(); //Metodo para cargar los asientos ocupados desde un archivo

    int limiteAsientos = 0; //Variable que almacena el límite de asientos seleccionables

    int seleccionados = 0; //Variable que almacena el número de asientos actualmente seleccionados
};

#endif // ASIENTOS_H
