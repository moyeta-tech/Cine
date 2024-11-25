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

// Constructor de la clase InicioSesion
InicioSesion::InicioSesion(QWidget *parent)
    : QDialog(parent)  // Llama al constructor base QDialog
    , ui(new Ui::InicioSesion)  // Inicializa la interfaz de usuario a partir del archivo .ui
{
    ui->setupUi(this);  // Configura la interfaz de usuario de acuerdo con el archivo .ui

    // Establecemos el título de la ventana
    this->setWindowTitle("Iniciar sesión");

    // Establecemos el icono de la ventana usando un archivo de imagen
    setWindowIcon(QIcon(":/images/src/icons/image cine.ico"));

    // Llamamos al slot para cargar el stylesheet (hoja de estilos)
    initstylesheet();

    // Conectamos los botones con los slots correspondientes para manejar los clics
    connect(ui->Boton_iniciar, &QPushButton::clicked, this, &InicioSesion::iniciarSesion);
    connect(ui->Boton_salir, &QPushButton::clicked, this, &InicioSesion::salirVentana);

    // Establecemos un icono de inicio de sesión en el label
    ui->label->setPixmap(QPixmap(":/images/src/icons/login.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Cargamos los ID de empleados desde el archivo CSV
    cargarEmpleados();
}

// Destructor de la clase InicioSesion
InicioSesion::~InicioSesion()
{
    delete ui;  // Libera la memoria utilizada por la interfaz de usuario
}

// Set estático que almacena los ID de los empleados cargados desde el archivo
QSet<QString> InicioSesion::empleadosIDs;

// Método para cargar los ID de los empleados desde un archivo CSV
void InicioSesion::cargarEmpleados()
{
    // Ruta del archivo CSV en la carpeta del proyecto
    qDebug() << QDir::currentPath();  // Imprime la ruta actual del directorio
    QString filePath = QDir::currentPath() + "/empleados.csv";  // Ruta completa del archivo CSV
    qDebug() << "Ruta del archivo de empleados:" << filePath;

    QFile file(filePath);  // Abre el archivo para leerlo
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Si no se puede abrir el archivo, mostramos un mensaje de error
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo de empleados.");
        return;
    }

    QTextStream in(&file);  // Flujo de texto para leer el contenido del archivo
    while (!in.atEnd()) {
        QString line = in.readLine();  // Lee cada línea del archivo
        QStringList columns = line.split(",");  // Divide la línea en columnas usando la coma como delimitador
        if (!columns.isEmpty()) {
            QString idEmpleado = columns[0].trimmed();  // Obtenemos solo el primer valor (ID)
            empleadosIDs.insert(idEmpleado);  // Insertamos el ID en el set
        }
    }
}

// Método para validar las credenciales del empleado (verificar si el ID existe en el set)
bool InicioSesion::validarCredenciales(const QString &usuario)
{
    // Verificamos si el ID de empleado existe en el set
    return empleadosIDs.contains(usuario);
}

// Método para iniciar sesión
void InicioSesion::iniciarSesion()
{
    qDebug() << "Iniciar sesion";

    QString usuario = ui->lineEdit_id->text();  // Obtenemos el ID de empleado ingresado por el usuario

    // Verificamos si el campo de ID está vacío
    if (usuario.isEmpty()) {
        QMessageBox::warning(this, "Campo Vacío", "Por favor, ingresa un ID de empleado.");
        return;  // Si el campo está vacío, salimos de la función
    }

    // Validamos las credenciales del usuario (si el ID existe)
    if (validarCredenciales(usuario)) {
        // Obtener el nombre del empleado con el ID
        QString nombreEmpleado = obtenerNombreEmpleado(usuario);

        // Crear la ventana de Cine
        Cine* cineWindow = new Cine();

        qDebug() << nombreEmpleado;
        // Establecer el título de la ventana con el nombre del empleado
        cineWindow->setWindowTitle("Bienvenido, " + nombreEmpleado);

        // Mostrar la ventana de Cine
        cineWindow->show();

        // Cerrar la ventana de inicio de sesión
        this->accept();
    } else {
        // Si las credenciales son incorrectas, mostramos un icono de error y un mensaje
        ui->label->setPixmap(QPixmap(":/images/src/icons/wrongpass.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QMessageBox::warning(this, "ID Incorrecto", "El ID de empleado no es válido.");
    }
}

// Método para obtener el nombre del empleado usando su ID
QString InicioSesion::obtenerNombreEmpleado(const QString &idEmpleado)
{
    QString filePath = QDir::currentPath() + "/empleados.csv";  // Ruta al archivo de empleados
    QFile file(filePath);  // Abrimos el archivo
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo de empleados.");
        return "";  // Si no se puede abrir el archivo, retornamos una cadena vacía
    }

    QTextStream in(&file);  // Flujo de texto para leer el archivo
    while (!in.atEnd()) {
        QString line = in.readLine();  // Leemos cada línea
        QStringList columns = line.split(",");  // Dividimos en columnas
        if (!columns.isEmpty() && columns[0].trimmed() == idEmpleado) {
            return columns[1].trimmed();  // Si encontramos el ID, retornamos el nombre que está en la segunda columna
        }
    }
    return "";  // Si no encontramos el ID, retornamos una cadena vacía
}

// Método para cerrar la ventana de inicio de sesión
void InicioSesion::salirVentana()
{
    this->close();  // Cierra solo la ventana actual (InicioSesion)
}

// Método para inicializar la hoja de estilos de la ventana
void InicioSesion::initstylesheet()
{
    // Abrimos el archivo de estilos que se encuentra en los recursos
    QFile style(":/src/stylesheet/stylesheet-inicio.css");
    bool styleOK = style.open(QFile::ReadOnly);  // Intentamos abrir el archivo de estilos
    qDebug() << "Apertura de archivo: " << styleOK;  // Imprimimos si el archivo se abrió correctamente
    QString stringEstilo = QString::fromLatin1(style.readAll());  // Leemos el contenido del archivo
    this->setStyleSheet(stringEstilo);  // Aplicamos el estilo a la ventana
}
