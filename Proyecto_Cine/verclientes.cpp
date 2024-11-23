#include "verclientes.h"
#include "ui_verclientes.h"
#include "clientes.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

VerClientes::VerClientes(const std::vector<Clientes*> &vectorClientesRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerClientes)
    , vectorClientes(vectorClientesRef)
{
    ui->setupUi(this);
    this->setWindowTitle("Lista de Clientes");

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // Configurar encabezados de la tabla
    ui->tableWidget->setColumnCount(6); // Número de columnas
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nombre", "Apellido", "DNI", "Edad", "Teléfono"});

    // Cargar datos desde archivo CSV
    QString rutaArchivo = QDir::currentPath() + "/clientes.csv";  // Cambia esto con la ruta correcta
    cargarClientesDesdeCSV(rutaArchivo);
}

VerClientes::~VerClientes()
{
    delete ui;
}

void VerClientes::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    if (style.open(QFile::ReadOnly)) {
        QString stringEstilo = QString::fromLatin1(style.readAll());
        this->setStyleSheet(stringEstilo);
    } else {
        qDebug() << "No se pudo cargar el archivo de estilo.";
    }
}

void VerClientes::cargarClientesDesdeCSV(const QString &archivo)
{
    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo CSV para lectura.";
        return;
    }

    QTextStream stream(&file);
    QString line;
    while (!stream.atEnd()) {
        line = stream.readLine();
        QStringList campos = line.split(',');

        // Verificar que la línea tenga el número correcto de campos
        if (campos.size() == 6) {  // Aseguramos que hay 6 campos (ID, Nombre, Apellido, DNI, Edad, Teléfono)
            int id = campos[0].toInt();
            QString nombre = campos[1];
            QString apellido = campos[2];
            int dni = campos[3].toInt();
            int edad = campos[4].toInt();
            int telefono = campos[5].toInt();

            // Agregar cliente a la tabla
            agregarClienteATabla(id, nombre, apellido, dni, edad, telefono);
        } else {
            qDebug() << "Línea inválida en el archivo: " << line;
        }
    }

    file.close();
}

void VerClientes::agregarClienteATabla(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nombre));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(apellido));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(dni)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(edad)));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(telefono)));
}

void VerClientes::cargarClientes()
{
    ui->tableWidget->setRowCount(0); // Limpiar cualquier contenido previo

    for (size_t i = 0; i < vectorClientes.size(); ++i) {
        Clientes *cliente = vectorClientes[i];

        // Crear una nueva fila en la tabla
        ui->tableWidget->insertRow(i);

        // Insertar los datos del cliente en las celdas correspondientes
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(cliente->getIDcliente())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(cliente->getNombre()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(cliente->getApellido()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(cliente->getDni())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(cliente->getEdad())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(cliente->getTelefono())));
    }

    // Ajustar automáticamente el tamaño de las columnas
    ui->tableWidget->resizeColumnsToContents();
}
