#include "empleados.h"
#include "ui_empleados.h"
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QDebug>

Empleados::Empleados(std::vector<Empleados*> &vectorEmpleadosRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Empleados)
    , vectorEmpleados(vectorEmpleadosRef)
{
    ui->setupUi(this);
    this->setWindowTitle("Formulario de empleados");
    initstylesheet();
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Empleados::registrarEmpleado);
}

Empleados::~Empleados()
{
    delete ui;
}

// Getters y Setters
int Empleados::getIDempleado() const { return idEmpleado; }
void Empleados::setIDempleado(int idempleado) { idEmpleado = idempleado; }
QString Empleados::getNombre() const { return Nombre; }
void Empleados::setNombre(const QString &nombre) { Nombre = nombre; }
QString Empleados::getApellido() const { return Apellido; }
void Empleados::setApellido(const QString &apellido) { Apellido = apellido; }
int Empleados::getDni() const { return Dni; }
void Empleados::setDni(int dni) { Dni = dni; }
int Empleados::getEdad() const { return Edad; }
void Empleados::setEdad(int edad) { Edad = edad; }
int Empleados::getTelefono() const { return Telefono; }
void Empleados::setTelefono(int telefono) { Telefono = telefono; }
QString Empleados::getPuesto() const { return Puesto; }
void Empleados::setPuesto(const QString &puesto) { Puesto = puesto; }

void Empleados::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    if (style.open(QFile::ReadOnly)) {
        QString stringEstilo = QString::fromLatin1(style.readAll());
        this->setStyleSheet(stringEstilo);
    } else {
        qDebug() << "No se pudo cargar el archivo de estilo.";
    }
}

void Empleados::registrarEmpleado()
{
    QString filePath = QDir::currentPath() + "/empleados.csv";

    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() ||
        ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() ||
        ui->lineEdit_5->text().isEmpty() || ui->lineEdit_6->text().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Todos los campos deben ser completados.");
        return;
    }

    Empleados *empleado = new Empleados(vectorEmpleados, this);
    empleado->setIDempleado(ui->lineEdit->text().toInt());
    empleado->setNombre(ui->lineEdit_2->text());
    empleado->setApellido(ui->lineEdit_3->text());
    empleado->setDni(ui->lineEdit_4->text().toInt());
    empleado->setEdad(ui->spinBox->value());
    empleado->setTelefono(ui->lineEdit_5->text().toInt());
    empleado->setPuesto(ui->lineEdit_6->text());

    vectorEmpleados.push_back(empleado);

    guardarEmpleadoEnCSV(filePath, *empleado);
    QMessageBox::information(this, "Empleado guardado", "Empleado registrado correctamente.");

    // Emitir la señal cuando el empleado se ha agregado correctamente
    emit empleadoAgregado(empleado->getIDempleado(), empleado->getNombre(), empleado->getApellido(),
                          empleado->getDni(), empleado->getEdad(), empleado->getTelefono(), empleado->getPuesto());
}

void Empleados::leerEmpleadosDesdeArchivo()
{
    QString filePath = QDir::currentPath() + "/empleados.csv";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    vectorEmpleados.clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() == 7) {
            Empleados *empleado = new Empleados(vectorEmpleados, this);
            empleado->setIDempleado(fields[0].toInt());
            empleado->setNombre(fields[1]);
            empleado->setApellido(fields[2]);
            empleado->setDni(fields[3].toInt());
            empleado->setEdad(fields[4].toInt());
            empleado->setTelefono(fields[5].toInt());
            empleado->setPuesto(fields[6]);
            vectorEmpleados.push_back(empleado);
        }
    }
    file.close();
}

// Funciones auxiliares
void guardarEmpleadoEnCSV(const QString &archivo, const Empleados &empleado)
{
    QFile file(archivo);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << empleado.getIDempleado() << ","
        << empleado.getNombre() << ","
        << empleado.getApellido() << ","
        << empleado.getDni() << ","
        << empleado.getEdad() << ","
        << empleado.getTelefono() << ","
        << empleado.getPuesto() << "\n";
    file.close();
}

void inicializarCSV(const QString &archivo)
{
    QFile file(archivo);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "ID,Nombre,Apellido,DNI,Edad,Telefono,Puesto\n";
            file.close();
        } else {
            qDebug() << "No se pudo inicializar el archivo:" << file.errorString();
        }
    }
}
