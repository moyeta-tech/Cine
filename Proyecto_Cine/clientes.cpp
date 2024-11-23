#include "clientes.h"
#include "ui_clientes.h"

Clientes::Clientes(std::vector<Clientes *> &vectorClientesRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Clientes)
    , vectorClientes(vectorClientesRef)
{
    ui->setupUi(this);
    this->setWindowTitle("Formulario de clientes");
    initstylesheet();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Clientes::registrarCliente);
}

Clientes::~Clientes()
{
    delete ui;
}

// Getters y Setters
int Clientes::getIDcliente() const { return idCliente; }
void Clientes::setIDcliente(int idcliente) { idCliente = idcliente; }
QString Clientes::getNombre() const { return Nombre; }
void Clientes::setNombre(const QString &nombre) { Nombre = nombre; }
QString Clientes::getApellido() const { return Apellido; }
void Clientes::setApellido(const QString &apellido) { Apellido = apellido; }
int Clientes::getDni() const { return Dni; }
void Clientes::setDni(int dni) { Dni = dni; }
int Clientes::getEdad() const { return Edad; }
void Clientes::setEdad(int edad) { Edad = edad; }
int Clientes::getTelefono() const { return Telefono; }
void Clientes::setTelefono(int telefono) { Telefono = telefono; }

void Clientes::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    if (style.open(QFile::ReadOnly)) {
        QString stringEstilo = QString::fromLatin1(style.readAll());
        this->setStyleSheet(stringEstilo);
    } else {
        qDebug() << "No se pudo cargar el archivo de estilo.";
    }
}

void Clientes::registrarCliente()
{
    QString filePath = QDir::currentPath() + "/clientes.csv";

    // Validar que todos los campos estén completos
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() ||
        ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() ||
        ui->lineEdit_5->text().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Todos los campos deben ser completados.");
        return;
    }

    // Crear un nuevo cliente con los datos del formulario
    Clientes *cliente = new Clientes(vectorClientes, this);
    cliente->setIDcliente(ui->lineEdit->text().toInt());
    cliente->setNombre(ui->lineEdit_2->text());
    cliente->setApellido(ui->lineEdit_3->text());
    cliente->setDni(ui->lineEdit_4->text().toInt());
    cliente->setEdad(ui->spinBox->value());
    cliente->setTelefono(ui->lineEdit_5->text().toInt());

    // Agregar el cliente al vector
    vectorClientes.push_back(cliente);

    // Guardar el cliente en el archivo CSV
    guardarClienteEnCSV(filePath, *cliente);

    // Mostrar mensaje de confirmación
    QMessageBox::information(this, "Cliente guardado", "Cliente registrado correctamente.");

    // Emitir señal para notificar que se ha agregado un nuevo cliente
    emit clienteAgregado(cliente->getIDcliente(), cliente->getNombre(), cliente->getApellido(),
                         cliente->getDni(), cliente->getEdad(), cliente->getTelefono());
}

void Clientes::leerClientesDesdeArchivo()
{
    QString filePath = QDir::currentPath() + "/clientes.csv";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    vectorClientes.clear(); // Limpiar el vector antes de agregar los nuevos datos

    // Leer el archivo línea por línea y crear clientes
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        // Verificar que la línea tenga el número correcto de campos
        if (fields.size() == 6) {
            Clientes *cliente = new Clientes(vectorClientes, this);
            cliente->setIDcliente(fields[0].toInt());
            cliente->setNombre(fields[1]);
            cliente->setApellido(fields[2]);
            cliente->setDni(fields[3].toInt());
            cliente->setEdad(fields[4].toInt());
            cliente->setTelefono(fields[5].toInt());

            vectorClientes.push_back(cliente); // Agregar al vector
        }
    }

    file.close();
}

// Función para guardar un cliente en el archivo CSV
void Clientes::guardarClienteEnCSV(const QString &archivo, const Clientes &cliente)
{
    QFile file(archivo);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << cliente.getIDcliente() << ","
        << cliente.getNombre() << ","
        << cliente.getApellido() << ","
        << cliente.getDni() << ","
        << cliente.getEdad() << ","
        << cliente.getTelefono() << "\n";

    file.close();
}

// Función para inicializar el archivo CSV con encabezados si no existe
void Clientes::inicializarCSV(const QString &archivo)
{
    QFile file(archivo);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "ID,Nombre,Apellido,DNI,Edad,Telefono\n"; // Encabezados
            file.close();
        } else {
            qDebug() << "No se pudo inicializar el archivo:" << file.errorString();
        }
    }
}
