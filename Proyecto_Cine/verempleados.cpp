#include "verempleados.h"
#include "ui_verempleados.h"
#include "empleados.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>

VerEmpleados::VerEmpleados(std::vector<Empleados*>& empleados, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerEmpleados),
    empleados(empleados)
{
    ui->setupUi(this);

    // Configurar el QTableWidget
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nombre", "Apellido", "DNI", "Edad", "Teléfono", "Puesto"});

    // Ruta del archivo CSV desde el directorio de ejecución
    QString rutaArchivo = QDir::currentPath() + "/empleados.csv";
    qDebug() << "Ruta para cargar archivo: " << rutaArchivo;

    // Cargar empleados desde el archivo CSV
    cargarEmpleadosDesdeCSV(rutaArchivo);
}

VerEmpleados::~VerEmpleados()
{
    delete ui;
}

void VerEmpleados::cargarEmpleadosDesdeCSV(const QString &archivo)
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
        if (campos.size() == 7) {
            int id = campos[0].toInt();
            QString nombre = campos[1];
            QString apellido = campos[2];
            int dni = campos[3].toInt();
            int edad = campos[4].toInt();
            int telefono = campos[5].toInt();
            QString puesto = campos[6];

            // Agregar empleado a la tabla
            agregarEmpleadoATabla(id, nombre, apellido, dni, edad, telefono, puesto);
        } else {
            qDebug() << "Línea inválida en el archivo: " << line;
        }
    }

    file.close();
}

void VerEmpleados::agregarEmpleadoATabla(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono, const QString &puesto)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nombre));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(apellido));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(dni)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(edad)));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(telefono)));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(puesto));
}
