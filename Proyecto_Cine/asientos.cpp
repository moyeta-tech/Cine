#include "asientos.h"               // Incluye el archivo de cabecera para la clase 'Asientos'.
#include "ui_asientos.h"            // Incluye la interfaz de usuario generada automáticamente para 'Asientos'.
#include "pago.h"                   // Incluye el archivo de cabecera para la clase 'Pago'.

#include <QDebug>                   // Incluye las funcionalidades para depurar en Qt.
#include <QMessageBox>              // Incluye las funcionalidades para mostrar mensajes emergentes.
#include <QFile>                    // Incluye las funcionalidades para manejar archivos.
#include <QTextStream>              // Incluye las funcionalidades para leer y escribir en archivos de texto.

Asientos::Asientos(QWidget *parent)    // Constructor de la clase 'Asientos'.
    : QDialog(parent)                   // Inicializa la clase base 'QDialog' pasando el padre.
    , ui(new Ui::Asientos)              // Inicializa la interfaz de usuario de 'Asientos'.
{
    ui->setupUi(this);                 // Configura la interfaz de usuario.

    // Establecemos el título de la ventana
    this->setWindowTitle("Paso 2: Selección de asiento");

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // Conectamos el botón continuar para llegar a la ventana de pago
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Asientos::continuarPago);

    // Inicializamos la lista de botones de los asientos
    botonesAsientos =
        {
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

    // Hacer que todos los botones sean checkable
    for (QPushButton* boton : botonesAsientos)
    {  // Recorre la lista de botones
        boton->setCheckable(true);                  // Hace que cada botón sea seleccionable (checkable)
    }

    // Cargar los asientos ocupados desde un archivo
    cargarAsientosOcupados();

    // Llamamos al método para marcar los asientos ocupados
    marcarAsientosOcupados();

    // Conectamos los botones de los asientos disponibles para seleccionarlos
    for (QPushButton* boton : botonesAsientos)
    {  // Recorre la lista de botones de asientos
        connect(boton, &QPushButton::clicked, this, &Asientos::seleccionarAsiento);  // Conecta el clic de cada botón con la función 'seleccionarAsiento'
    }
}

Asientos::~Asientos()  // Destructor de la clase 'Asientos'
{
    delete ui;  // Libera los recursos de la interfaz de usuario
}

// GET Y SET DE NUMERO
int Asientos::getNumero()  // Método para obtener el número de asiento
{
    return Numero;  // Devuelve el número de asiento
}
void Asientos::setNumero(int numero)  // Método para establecer el número de asiento
{
    Numero = numero;  // Asigna el número pasado como parámetro
}

// GET Y SET DE FILA
QString Asientos::getFila()  // Método para obtener la fila del asiento
{
    return Fila;  // Devuelve el nombre de la fila
}

void Asientos::setFila(QString fila)  // Método para establecer la fila del asiento
{
    Fila = fila;  // Asigna la fila pasada como parámetro
}

void Asientos::continuarPago()  // Método para continuar con el proceso de pago
{
    // Recolectar los asientos seleccionados
    QStringList asientosSeleccionados;  // Lista que almacenará los asientos seleccionados
    for (QPushButton* boton : botonesAsientos)
    {  // Recorre los botones de los asientos
        if (boton->isChecked())
        {  // Si el asiento está marcado
            asientosSeleccionados.append(boton->text());  // Agrega el texto (número del asiento) a la lista
        }
    }

    // Recolectar otros datos relevantes
    QString metodo = "Tarjeta";  // Ejemplo de método de pago (puede ser cambiado)
    float monto = 100.0f;        // Monto total (puedes calcularlo según las entradas seleccionadas)
    QString fecha = "2024-11-11";  // Fecha actual o seleccionada

    // Pasar los datos al diálogo de Pago
    Pago dialog(metodo, monto, fecha, this);  // Crea un objeto de la clase 'Pago'
    dialog.setAsientos(asientosSeleccionados.join(", "));  // Envía los asientos seleccionados al diálogo de pago
    dialog.exec();  // Ejecuta el diálogo de pago
}

QStringList Asientos::getAsientosSeleccionados() const
{  // Método para obtener los asientos seleccionados
    return asientosSeleccionados;  // Devuelve la lista de asientos seleccionados
}

void Asientos::initstylesheet()  // Método para inicializar el estilo de la interfaz
{
    QFile style(":/src/stylesheet/stylesheet-asientos.css");  // Abre el archivo CSS que define el estilo
    bool styleOK = style.open(QFile::ReadOnly);  // Intenta abrir el archivo en modo solo lectura
    qDebug() << "Apertura de archivos: " <<styleOK;  // Muestra en el log si el archivo se abrió correctamente
    QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el contenido del archivo CSS
    this->setStyleSheet(stringEstilo);  // Aplica el estilo a la interfaz de usuario
}

void Asientos::marcarAsientosOcupados()  // Método para marcar los asientos ocupados
{
    // Recorrer todos los botones de la lista
    for (int i = 0; i < botonesAsientos.size(); ++i)
    {  // Itera sobre todos los asientos
        if (asientosOcupados.contains(i))
        {  // Si el asiento está en la lista de ocupados
            // Cambiar el estilo del botón a rojo para indicar ocupado
            botonesAsientos[i]->setStyleSheet("background-color: red; color: white;");
            botonesAsientos[i]->setEnabled(false);  // Desactiva el botón (ya no puede ser seleccionado)
        }
        else
        {
            // Estilo por defecto para los asientos libres
            botonesAsientos[i]->setStyleSheet("background-color: green; color: white;");
            botonesAsientos[i]->setEnabled(true);  // Activa el botón (puede ser seleccionado)
        }
    }
}

void Asientos::setLimiteAsientos(int limite)
{  // Establece el límite de asientos seleccionables
    limiteAsientos = limite;  // Asigna el límite de asientos
}

void Asientos::seleccionarAsiento()
{  // Método que se ejecuta cuando se selecciona un asiento
    QPushButton* boton = qobject_cast<QPushButton*>(sender());  // Obtiene el botón que fue presionado
    if (boton) {
        if (boton->isChecked())
        {  // Si el botón está marcado
            // Si el asiento estaba desmarcado, se marca
            boton->setStyleSheet("background-color: yellow; color: black;");
            seleccionados++;  // Incrementa el contador de asientos seleccionados
        }
        else
        {
            // Si el asiento estaba marcado, se desmarca
            boton->setStyleSheet("background-color: green; color: white;");
            seleccionados--;  // Decrementa el contador de asientos seleccionados
        }

        // Asegurar que no exceda el límite de asientos
        if (seleccionados > limiteAsientos)
        {  // Si se excede el límite
            // Desmarcar el último asiento seleccionado
            boton->setChecked(false);
            seleccionados--;  // Decrementa el contador
            QMessageBox::warning(this, "Límite alcanzado",  // Muestra un mensaje de advertencia
                                 "No puedes seleccionar más asientos que los indicados.");
        }
    }
}

void Asientos::actualizarAsientoOcupado(int indice)  // Método para actualizar el estado de un asiento como ocupado
{
    if (!asientosOcupados.contains(indice))
    {  // Si el asiento no está marcado como ocupado
        asientosOcupados.append(indice);  // Añade el asiento a la lista de ocupados
        // Guardar los asientos ocupados en un archivo
        guardarAsientosOcupados();
        // Marcar el asiento como ocupado (rojo)
        botonesAsientos[indice]->setStyleSheet("background-color: red; color: white;");
        botonesAsientos[indice]->setEnabled(false);  // Desactiva el botón
    }
}

void Asientos::guardarAsientosOcupados()  // Método para guardar la lista de asientos ocupados en un archivo
{
    QFile file("asientos_ocupados.txt");  // Abre el archivo de texto para escribir los asientos ocupados
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {  // Si el archivo se puede abrir para escritura
        QTextStream out(&file);  // Crea un flujo de texto para escribir en el archivo
        for (int i = 0; i < asientosOcupados.size(); ++i)
        {  // Recorre la lista de asientos ocupados
            out << asientosOcupados[i] << "\n";  // Escribe cada asiento en el archivo
        }
        file.close();  // Cierra el archivo después de escribir
    }
}

void Asientos::cargarAsientosOcupados()  // Método para cargar la lista de asientos ocupados desde un archivo
{
    QFile file("asientos_ocupados.txt");  // Abre el archivo de texto con los asientos ocupados
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {  // Si el archivo se puede abrir para lectura
        QTextStream in(&file);  // Crea un flujo de texto para leer desde el archivo
        asientosOcupados.clear();  // Limpia la lista de asientos ocupados
        while (!in.atEnd())
        {  // Mientras no se haya alcanzado el final del archivo
            QString line = in.readLine();  // Lee una línea del archivo
            asientosOcupados.append(line.toInt());  // Convierte la línea a entero y lo agrega a la lista
        }
        file.close();  // Cierra el archivo después de leer
    }
}
