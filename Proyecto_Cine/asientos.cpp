#include "asientos.h"
#include "ui_asientos.h"

#include "pago.h"

#include <QDebug>
#include <QMessageBox>

Asientos::Asientos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Asientos)
{
    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Paso 2: Seleccion de asiento");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    //Conectamos el boton continuar para llegar a la ventana de pago
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Asientos::continuarPago);

    // Inicializamos la lista de botones de los asientos
    botonesAsientos = {
        ui->A1, ui->A2, ui->A3, ui->A4, ui->A5, ui->A6, ui->A7, ui->A8,
        ui->B1, ui->B2, ui->B3, ui->B4, ui->B5, ui->B6, ui->B7, ui->B8,
        ui->C1, ui->C2, ui->C3, ui->C4, ui->C5, ui->C6, ui->C7, ui->C8,
        ui->D5, ui->D6, ui->D7, ui->D8,
        ui->E5, ui->E6, ui->E7, ui->E8,
        ui->F1, ui->F2, ui->F5, ui->F6, ui->F7, ui->F8,
        ui->G1, ui->G2, ui->G5, ui->G6, ui->G7, ui->G8,
        ui->H1, ui->H2, ui->H5, ui->H6, ui->H7, ui->H8,
        ui->I1, ui->I2, ui->I3, ui->I4, ui->I5, ui->I6, ui->I7, ui->I8
    };

    // Cargar los asientos ocupados desde un archivo
    cargarAsientosOcupados();

    // Llamamos al método para marcar los asientos ocupados
    marcarAsientosOcupados();

    // Conectamos los botones de los asientos disponibles para seleccionarlos
    for (QPushButton* boton : botonesAsientos) {
        connect(boton, &QPushButton::clicked, this, &Asientos::seleccionarAsiento);
    }
}

Asientos::~Asientos()
{
    delete ui;
}

// GET Y SET DE NUMERO

int Asientos::getNumero()
{
    return Numero;
}
void Asientos::setNumero(int numero)
{
    Numero = numero;
}

// GET Y SET DE FILA

QString Asientos::getFila()
{
    return Fila;
}


void Asientos::setFila(QString fila)
{
    Fila = fila;
}

void Asientos::continuarPago()
{
    // Recolectar los asientos seleccionados
    QStringList asientosSeleccionados;
    for (QPushButton* boton : botonesAsientos) {
        if (boton->isChecked()) {
            asientosSeleccionados.append(boton->text());
        }
    }

    // Recolectar otros datos relevantes
    QString metodo = "Tarjeta"; // Ejemplo: puedes obtenerlo desde otro lugar si es necesario
    float monto = 100.0f;       // Monto total (puedes calcularlo según entradas seleccionadas)
    QString fecha = "2024-11-11"; // Fecha actual o seleccionada

    // Pasar los datos al diálogo de Pago
    Pago dialog(metodo, monto, fecha, this);
    dialog.setAsientos(asientosSeleccionados.join(", ")); // Método personalizado para los asientos
    dialog.exec();
}

QStringList Asientos::getAsientosSeleccionados() const {
    return asientosSeleccionados; // Devuelve la lista de asientos seleccionados
}

// HOJA DE ESTILOS
void Asientos::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-asientos.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

// MÉTODO PARA INICIALIZAR Y MARCAR LOS ASIENTOS OCUPADOS
void Asientos::marcarAsientosOcupados()
{
    // Recorrer todos los botones de la lista
    for (int i = 0; i < botonesAsientos.size(); ++i) {
        if (asientosOcupados.contains(i)) {
            // Cambiar el estilo del botón a rojo para indicar ocupado
            botonesAsientos[i]->setStyleSheet("background-color: red; color: white;");
            botonesAsientos[i]->setEnabled(false); // Desactivar el botón
        } else {
            // Estilo por defecto para los asientos libres
            botonesAsientos[i]->setStyleSheet("background-color: green; color: white;");
            botonesAsientos[i]->setEnabled(true); // Activar el botón
        }
    }
}

void Asientos::setLimiteAsientos(int limite) {
    limiteAsientos = limite;
}

// MÉTODO PARA SELECCIONAR UN ASIENTO
void Asientos::seleccionarAsiento() {
    QPushButton* boton = qobject_cast<QPushButton*>(sender());
    if (boton) {
        if (boton->isChecked()) {
            // Si el asiento ya estaba seleccionado, desmarcar
            boton->setChecked(false);
            boton->setStyleSheet("background-color: green; color: white;");
            seleccionados--;
        } else {
            if (seleccionados < limiteAsientos) {
                // Permitir seleccionar si no excede el límite
                boton->setChecked(true);
                boton->setStyleSheet("background-color: yellow; color: black;");
                seleccionados++;
            } else {
                // Mostrar un mensaje si intenta seleccionar más de lo permitido
                QMessageBox::warning(this, "Límite alcanzado",
                                     "No puedes seleccionar más asientos que los indicados.");
            }
        }
    }
}

// ACTUALIZAR UN ASIENTO A OCUPADO
void Asientos::actualizarAsientoOcupado(int indice)
{
    if (!asientosOcupados.contains(indice)) {
        asientosOcupados.append(indice);
        // Guardar los asientos ocupados en un archivo
        guardarAsientosOcupados();
        // Marcar el asiento como ocupado (rojo)
        botonesAsientos[indice]->setStyleSheet("background-color: red; color: white;");
        botonesAsientos[indice]->setEnabled(false); // Desactivar el botón
    }
}

// GUARDAR LOS ASIENTOS OCUPADOS EN UN ARCHIVO
void Asientos::guardarAsientosOcupados()
{

}

// CARGAR LOS ASIENTOS OCUPADOS DESDE UN ARCHIVO
void Asientos::cargarAsientosOcupados()
{

}

