#include "verclientes.h"
#include "ui_verclientes.h"

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

    // Cargar datos en la tabla
    cargarClientes();
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
