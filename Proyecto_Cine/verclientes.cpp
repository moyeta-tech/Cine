#include "verclientes.h"
#include "ui_verclientes.h"
#include "clientes.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

VerClientes::VerClientes(const std::vector<Clientes*> &vectorClientesRef, QWidget *parent)
    : QDialog(parent)  // Constructor de la clase VerClientes
    , ui(new Ui::VerClientes)  // Inicializa la interfaz de usuario
    , vectorClientes(vectorClientesRef)  // Inicializa el vector de clientes
{
    ui->setupUi(this);  // Configura la interfaz de usuario con el archivo .ui

    this->setWindowTitle("Lista de Clientes");  // Establece el título de la ventana

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();  // Aplica un archivo de estilo a la ventana

    // Configurar encabezados de la tabla
    ui->tableWidget->setColumnCount(6);  // Define el número de columnas en la tabla
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nombre", "Apellido", "DNI", "Edad", "Teléfono"});  // Asigna etiquetas a las columnas de la tabla

    // Cargar datos desde archivo CSV
    QString rutaArchivo = QDir::currentPath() + "/clientes.csv";  // Define la ruta del archivo CSV de clientes
    cargarClientesDesdeCSV(rutaArchivo);  // Llama a la función para cargar los clientes desde el archivo CSV
}

VerClientes::~VerClientes()  // Destructor de la clase VerClientes
{
    delete ui;  // Libera la memoria de la interfaz de usuario
}

void VerClientes::initstylesheet()  // Función para cargar y aplicar el estilo desde un archivo
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Abre el archivo de estilo
    if (style.open(QFile::ReadOnly)) {  // Si el archivo se abre correctamente
        QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee todo el contenido del archivo
        this->setStyleSheet(stringEstilo);  // Aplica el estilo a la ventana
    } else {
        qDebug() << "No se pudo cargar el archivo de estilo.";  // Imprime un mensaje si no se puede cargar el archivo de estilo
    }
}

void VerClientes::cargarClientesDesdeCSV(const QString &archivo)  // Función para cargar los clientes desde un archivo CSV
{
    QFile file(archivo);  // Crea un objeto QFile para abrir el archivo
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // Abre el archivo en modo solo lectura
        qDebug() << "No se pudo abrir el archivo CSV para lectura.";  // Imprime un mensaje si no se puede abrir el archivo
        return;  // Sale de la función si el archivo no se puede abrir
    }

    QTextStream stream(&file);  // Crea un flujo de texto para leer el archivo
    QString line;  // Variable para almacenar cada línea del archivo
    while (!stream.atEnd()) {  // Mientras no se llegue al final del archivo
        line = stream.readLine();  // Lee una línea del archivo
        QStringList campos = line.split(',');  // Divide la línea en partes usando la coma como delimitador

        // Verificar que la línea tenga el número correcto de campos
        if (campos.size() == 6) {  // Aseguramos que hay 6 campos (ID, Nombre, Apellido, DNI, Edad, Teléfono)
            int id = campos[0].toInt();  // Convierte el primer campo a entero (ID)
            QString nombre = campos[1];  // El segundo campo es el nombre
            QString apellido = campos[2];  // El tercer campo es el apellido
            int dni = campos[3].toInt();  // El cuarto campo es el DNI
            int edad = campos[4].toInt();  // El quinto campo es la edad
            int telefono = campos[5].toInt();  // El sexto campo es el teléfono

            // Agregar cliente a la tabla
            agregarClienteATabla(id, nombre, apellido, dni, edad, telefono);  // Llama a la función para agregar el cliente a la tabla
        } else {
            qDebug() << "Línea inválida en el archivo: " << line;  // Imprime un mensaje si la línea no tiene el número correcto de campos
        }
    }

    file.close();  // Cierra el archivo después de leerlo
}

void VerClientes::agregarClienteATabla(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono)  // Función para agregar un cliente a la tabla
{
    int row = ui->tableWidget->rowCount();  // Obtiene el número de filas actuales en la tabla
    ui->tableWidget->insertRow(row);  // Inserta una nueva fila en la tabla

    // Inserta los datos del cliente en las celdas correspondientes
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));  // Inserta el ID en la primera columna
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nombre));  // Inserta el nombre en la segunda columna
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(apellido));  // Inserta el apellido en la tercera columna
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(dni)));  // Inserta el DNI en la cuarta columna
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(edad)));  // Inserta la edad en la quinta columna
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(telefono)));  // Inserta el teléfono en la sexta columna
}

void VerClientes::cargarClientes()  // Función para cargar los clientes en la tabla
{
    ui->tableWidget->setRowCount(0);  // Limpiar cualquier contenido previo de la tabla

    for (size_t i = 0; i < vectorClientes.size(); ++i) {  // Recorre el vector de clientes
        Clientes *cliente = vectorClientes[i];  // Obtiene el cliente de la posición actual en el vector

        // Crear una nueva fila en la tabla
        ui->tableWidget->insertRow(i);  // Inserta una fila en la tabla

        // Inserta los datos del cliente en las celdas correspondientes
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(cliente->getIDcliente())));  // Inserta el ID del cliente
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(cliente->getNombre()));  // Inserta el nombre del cliente
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(cliente->getApellido()));  // Inserta el apellido del cliente
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(cliente->getDni())));  // Inserta el DNI del cliente
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(cliente->getEdad())));  // Inserta la edad del cliente
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(cliente->getTelefono())));  // Inserta el teléfono del cliente
    }

    // Ajustar automáticamente el tamaño de las columnas
    ui->tableWidget->resizeColumnsToContents();  // Ajusta el tamaño de las columnas a su contenido
}
