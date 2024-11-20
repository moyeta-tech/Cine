#include "iniciosesion.h"
#include "ui_iniciosesion.h"

#include "cine.h"

#include <QMessageBox>
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QSet>
#include <QDir>
#include <QDebug>

InicioSesion::InicioSesion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InicioSesion)
{
    ui->setupUi(this);

    // Establecemos el título de la ventana
    this->setWindowTitle("Iniciar sesión");

    // Establecemos el icono de la ventana
    setWindowIcon(QIcon(":/images/src/icons/image cine.ico"));

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // Conectamos los botones con los slots correspondientes
    connect(ui->Boton_iniciar, &QPushButton::clicked, this, &InicioSesion::iniciarSesion);
    connect(ui->Boton_salir, &QPushButton::clicked, this, &InicioSesion::salirVentana);

    // Establecemos un icono de inicio de sesión
    ui->label->setPixmap(QPixmap(":/images/src/icons/login.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Cargar los ID de empleados desde el archivo CSV
    cargarEmpleados();
}

InicioSesion::~InicioSesion()
{
    delete ui;
}

QSet<QString> InicioSesion::empleadosIDs;  // Set estático para almacenar los ID de empleados

void InicioSesion::cargarEmpleados()
{
    // Ruta fija para el archivo CSV (actualiza la ruta con la que mencionas)
    QString filePath = "C:/Users/anitg/OneDrive/Documents/GitHub/Cine/Proyecto_Cine/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/empleados.csv";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo de empleados.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList columns = line.split(",");  // Suponiendo que el archivo CSV usa comas como delimitador
        if (!columns.isEmpty()) {
            QString idEmpleado = columns[0].trimmed();  // Obtenemos solo el primer valor (ID)
            empleadosIDs.insert(idEmpleado);  // Insertamos el ID en el set
        }
    }
}

bool InicioSesion::validarCredenciales(const QString &usuario)
{
    // Validamos si el ID de empleado existe en el set
    return empleadosIDs.contains(usuario);
}

void InicioSesion::iniciarSesion()
{
    QString usuario = ui->lineEdit_id->text();

    if (usuario.isEmpty())
    {
        QMessageBox::warning(this, "Campo Vacío", "Por favor, ingresa un ID de empleado.");
        return;
    }

    if (validarCredenciales(usuario))
    {
        // Obtener el nombre del empleado con el ID
        QString nombreEmpleado = obtenerNombreEmpleado(usuario);

        // Crear la ventana de Cine
        Cine* cineWindow = new Cine();

        // Establecer el título con el nombre del empleado
        cineWindow->setWindowTitle("Bienvenido, " + nombreEmpleado);

        // Mostrar la ventana de Cine
        cineWindow->show();

        // Cerrar la ventana de inicio de sesión
        this->accept();
    }
    else
    {
        ui->label->setPixmap(QPixmap(":/images/src/icons/wrongpass.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QMessageBox::warning(this, "ID Incorrecto", "El ID de empleado no es válido.");
    }
}


QString InicioSesion::obtenerNombreEmpleado(const QString &idEmpleado)
{
    QFile file("C:/Users/anitg/OneDrive/Documents/GitHub/Cine/Proyecto_Cine/build/Desktop_Qt_6_7_2_MinGW_64_bit-Debug/empleados.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo de empleados.");
        return "";
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList columns = line.split(",");
        if (!columns.isEmpty() && columns[0].trimmed() == idEmpleado) {
            return columns[1].trimmed();  // Supongamos que el nombre está en la segunda columna
        }
    }
    return "";  // Si no se encuentra el empleado
}


void InicioSesion::salirVentana()
{
    this->close();  // Cierra solo la ventana actual (InicioSesion)
}

void InicioSesion::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-inicio.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivo: " << styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
