#include "empleados.h"
#include "ui_empleados.h"

#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

Empleados::Empleados(std::vector<Empleados *> &vectorEmpleadosRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Empleados)
    , vectorEmpleados(vectorEmpleadosRef)
{
    ui->setupUi(this);

    // Establecemos el título de la ventana
    this->setWindowTitle("Formulario de empleados");

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // Imprimir el directorio de trabajo actual
    qDebug() << "Directorio actual: " << QDir::currentPath();

    // Conectar el botón de aceptar con la función para registrar el empleado
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Empleados::registrarEmpleado);

}

Empleados::Empleados(std::vector<Empleados *> &vectorEmpleadosRef, int idempleado, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto)
    : vectorEmpleados(vectorEmpleadosRef)
    , idEmpleado(idempleado)
    , Nombre(nombre)
    , Apellido(apellido)
    , Dni(dni)
    , Edad(edad)
    , Telefono(telefono)
    , Puesto(puesto)
{}

Empleados::~Empleados()
{
    delete ui;

    for(Empleados *empleado : vectorEmpleados){
        delete empleado;
    }
    vectorEmpleados.clear();
}

// GET Y SET DE IDEMPLEADO

int Empleados::getIDempleado()
{
    return idEmpleado;
}

void Empleados::setIDempleado(int idempleado)
{
    idEmpleado = idempleado;
}

// GET Y SET DE NOMBRE

QString Empleados::getNombre(){
    return Nombre;
}

void Empleados::setNombre(QString nombre){
    Nombre = nombre;
}

// GET Y SET DE APELLIDO

QString Empleados::getApellido(){
    return Apellido;
}

void Empleados::setApellido(QString apellido){
    Apellido = apellido;
}

// GET Y SET DE DNI

int Empleados::getDni(){
    return Dni;
}

void Empleados::setDni(int dni){
    Dni = dni;
}

// GET Y SET DE EDAD

int Empleados::getEdad(){
    return Edad;
}

void Empleados::setEdad(int edad){
    Edad = edad;
}

// GET Y SET DE TELEFONO

int Empleados::getTelefono(){
    return Telefono;
}

void Empleados::setTelefono(int telefono){
    Telefono = telefono;
}

// GET Y SET DE PUESTO

QString Empleados::getPuesto(){
    return Puesto;
}

void Empleados::setPuesto(QString puesto){
    Puesto = puesto;
}

void Empleados::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " << styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

void Empleados::registrarEmpleado()
{
    // Verificar si el empleado ya está en el archivo
    for (Empleados* e : vectorEmpleados) {
        if (e->getIDempleado() == ui->lineEdit->text().toInt()) {
            QMessageBox::warning(this, "Advertencia", "El empleado ya está registrado.");
            return;
        }
    }

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

    emit empleadoAgregado(empleado->getIDempleado(), empleado->getNombre(),
                          empleado->getApellido(), empleado->getDni(),
                          empleado->getEdad(), empleado->getTelefono(),
                          empleado->getPuesto());
}


void Empleados::leerEmpleadosDesdeArchivo()
{
    // Limpiar el vector antes de cargar empleados
    for (Empleados* empleado : vectorEmpleados) {
        delete empleado;
    }
    vectorEmpleados.clear();

    // Obtener la ruta del archivo CSV
    QString filePath = QDir::currentPath() + "/empleados.csv";

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {

            QString line = in.readLine().trimmed();
            if(line.isEmpty()){ // IGNORAR LINEAS VACIAS
                continue;
            }
            QStringList fields = line.split(",");

            if (fields.size() == 7) {  // Asegurarse de que hay 7 campos (ID, Nombre, Apellido, DNI, Edad, Teléfono, Puesto)
                    Empleados *empleado = new Empleados(vectorEmpleados, this);
                    empleado->setIDempleado(fields[0].toInt());
                    empleado->setNombre(fields[1]);
                    empleado->setApellido(fields[2]);
                    empleado->setDni(fields[3].toInt());
                    empleado->setEdad(fields[4].toInt());
                    empleado->setTelefono(fields[5].toInt());
                    empleado->setPuesto(fields[6]);

                    vectorEmpleados.push_back(empleado);

            } else {
                qDebug() << "Formato de línea incorrecto en el archivo, lineas encontradas: " << fields.size();
                qDebug() << "Campos leidos: " << fields;
            }
        }
        file.close();
    } else {
        qDebug() << "No se pudo abrir el archivo para leer los empleados desde: " << filePath;
    }
}

void Empleados::agregarEmpleadoVectorArchivo(Empleados *empleado){

    // Obtener la ruta del directorio actual y el archivo CSV
    QString filePath = QDir::currentPath() + "/empleados.csv";
    qDebug() << "Ruta donde se intenta guardar el archivo:" << filePath;

    QFile file(filePath);

    // Crear el archivo si no existe

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
            while(!in.atEnd()){
            QString line = in.readLine();
                QStringList fields = line.split(',');
            if(fields[0].toInt() == empleado->getIDempleado()){
                    QMessageBox::warning(this, "Advertencia", "El empleado ya esta registrado con ese ID");
                    file.close();
                    return;
                }
            }
            file.close();

        }
        // AGREGAR AL VECTOR
        vectorEmpleados.push_back(empleado);

        // ABRIR ARCHIVO PARA AGREGAR AL FINAL
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "No se pudo crear el archivo CSV:\n" + file.errorString());
            return;
        }

    QTextStream out(&file);
    out << empleado->getIDempleado() << ","
        << empleado->getNombre() << ","
        << empleado->getApellido() << ","
        << empleado->getDni() << ","
        << empleado->getEdad() << ","
        << empleado->getTelefono() << ","
        << empleado->getPuesto() << "\n";

    file.close();

    qDebug() << "Empleado guardado correctamente en el archivo.";
    QMessageBox::information(this, "Empleado guardado",
                             "El empleado ha sido registrado con éxito.\n"
                             "Los datos se guardaron en:\n" + filePath);
}

