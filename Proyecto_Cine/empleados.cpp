#include "empleados.h"
#include "ui_empleados.h"
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QDebug>

Empleados::Empleados(std::vector<Empleados*> &vectorEmpleadosRef, QWidget *parent)
    : QDialog(parent)                   // Llama al constructor de la clase base QDialog.
    , ui(new Ui::Empleados)             // Crea el puntero de la interfaz de usuario.
    , vectorEmpleados(vectorEmpleadosRef) // Inicializa la referencia al vector de empleados.
{
    ui->setupUi(this);                  // Configura la interfaz de usuario.
    this->setWindowTitle("Formulario de empleados");  // Establece el título de la ventana.
    initstylesheet();                   // Llama a la función para cargar el estilo (CSS).

    // Conecta el botón 'Aceptar' del cuadro de diálogo con el método de registro de empleado.
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Empleados::registrarEmpleado);
}

Empleados::~Empleados()
{
    delete ui;  // Libera la memoria utilizada por la interfaz de usuario.
}

// Métodos Getter y Setter para los atributos del empleado.
int Empleados::getIDempleado() const
{
    return idEmpleado;
}

void Empleados::setIDempleado(int idempleado)
{
    idEmpleado = idempleado;
}

QString Empleados::getNombre() const
{
    return Nombre;
}

void Empleados::setNombre(const QString &nombre)
{
    Nombre = nombre;
}

QString Empleados::getApellido() const
{
    return Apellido;
}

void Empleados::setApellido(const QString &apellido)
{
    Apellido = apellido;
}

int Empleados::getDni() const
{
    return Dni;
}

void Empleados::setDni(int dni)
{
    Dni = dni;
}

int Empleados::getEdad() const
{
    return Edad;
}

void Empleados::setEdad(int edad)
{
    Edad = edad;
}

int Empleados::getTelefono() const
{
    return Telefono;
}

void Empleados::setTelefono(int telefono)
{
    Telefono = telefono;
}

QString Empleados::getPuesto() const
{
    return Puesto;
}

void Empleados::setPuesto(const QString &puesto)
{
    Puesto = puesto;
}

// Función para inicializar la hoja de estilo de la ventana.
void Empleados::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Ruta al archivo de estilos CSS.
    if (style.open(QFile::ReadOnly)) {  // Intenta abrir el archivo en modo solo lectura.
        QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el archivo CSS.
        this->setStyleSheet(stringEstilo);  // Aplica el estilo a la ventana.
    } else {
        qDebug() << "No se pudo cargar el archivo de estilo.";  // En caso de error al cargar el estilo.
    }
}

// Método que registra un empleado.
void Empleados::registrarEmpleado()
{
    QString filePath = QDir::currentPath() + "/empleados.csv";  // Ruta al archivo CSV donde se guardarán los empleados.

    // Verifica que todos los campos estén completos.
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() ||
        ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() ||
        ui->lineEdit_5->text().isEmpty() || ui->lineEdit_6->text().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Todos los campos deben ser completados.");
        return;  // Si algún campo está vacío, muestra una advertencia y termina la función.
    }

    // Crea un nuevo objeto Empleado con los datos del formulario.
    Empleados *empleado = new Empleados(vectorEmpleados, this);
    empleado->setIDempleado(ui->lineEdit->text().toInt());
    empleado->setNombre(ui->lineEdit_2->text());
    empleado->setApellido(ui->lineEdit_3->text());
    empleado->setDni(ui->lineEdit_4->text().toInt());
    empleado->setEdad(ui->spinBox->value());
    empleado->setTelefono(ui->lineEdit_5->text().toInt());
    empleado->setPuesto(ui->lineEdit_6->text());

    // Agrega el empleado al vector de empleados.
    vectorEmpleados.push_back(empleado);

    // Guarda el empleado en el archivo CSV.
    guardarEmpleadoEnCSV(filePath, *empleado);

    // Muestra un mensaje de confirmación.
    QMessageBox::information(this, "Empleado guardado", "Empleado registrado correctamente.");

    // Emite una señal cuando el empleado se ha agregado correctamente.
    emit empleadoAgregado(empleado->getIDempleado(), empleado->getNombre(), empleado->getApellido(),
                          empleado->getDni(), empleado->getEdad(), empleado->getTelefono(), empleado->getPuesto());
}

// Función que lee los empleados desde el archivo CSV.
void Empleados::leerEmpleadosDesdeArchivo()
{
    QString filePath = QDir::currentPath() + "/empleados.csv";  // Ruta al archivo CSV.
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // Abre el archivo para lectura.
        qDebug() << "Error al abrir el archivo:" << file.errorString();  // Si falla al abrirlo, muestra el error.
        return;
    }

    QTextStream in(&file);  // Prepara el flujo de texto para leer el archivo.
    vectorEmpleados.clear();  // Limpia el vector de empleados antes de cargar los nuevos datos.

    // Lee el archivo línea por línea.
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');  // Separa los campos de cada línea.
        if (fields.size() == 7) {  // Si la línea tiene los 7 campos esperados.
            // Crea un objeto Empleado a partir de los datos leídos.
            Empleados *empleado = new Empleados(vectorEmpleados, this);
            empleado->setIDempleado(fields[0].toInt());
            empleado->setNombre(fields[1]);
            empleado->setApellido(fields[2]);
            empleado->setDni(fields[3].toInt());
            empleado->setEdad(fields[4].toInt());
            empleado->setTelefono(fields[5].toInt());
            empleado->setPuesto(fields[6]);
            // Agrega el empleado al vector.
            vectorEmpleados.push_back(empleado);
        }
    }
    file.close();  // Cierra el archivo después de leerlo.
}

// Función para guardar un empleado en el archivo CSV.
void guardarEmpleadoEnCSV(const QString &archivo, const Empleados &empleado)
{
    QFile file(archivo);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {  // Abre el archivo en modo append (agregar al final).
        qDebug() << "Error al abrir el archivo:" << file.errorString();  // Si no se puede abrir el archivo, muestra un error.
        return;
    }

    QTextStream out(&file);  // Prepara el flujo de salida para escribir en el archivo.
    out << empleado.getIDempleado() << ","  // Escribe los datos del empleado en formato CSV.
        << empleado.getNombre() << ","
        << empleado.getApellido() << ","
        << empleado.getDni() << ","
        << empleado.getEdad() << ","
        << empleado.getTelefono() << ","
        << empleado.getPuesto() << "\n";
    file.close();  // Cierra el archivo después de escribir los datos.
}

// Función para inicializar el archivo CSV con los encabezados si no existe.
void inicializarCSV(const QString &archivo)
{
    QFile file(archivo);
    if (!file.exists()) {  // Verifica si el archivo ya existe.
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {  // Si no existe, lo crea.
            QTextStream out(&file);
            out << "ID,Nombre,Apellido,DNI,Edad,Telefono,Puesto\n";  // Escribe los encabezados en el archivo CSV.
            file.close();  // Cierra el archivo después de escribir los encabezados.
        } else {
            qDebug() << "No se pudo inicializar el archivo:" << file.errorString();  // Muestra el error si no se puede abrir el archivo.
        }
    }
}
