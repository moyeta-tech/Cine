#include "clientes.h"
#include "ui_clientes.h"

Clientes::Clientes(std::vector<Clientes *> &vectorClientesRef, QWidget *parent)
    : QDialog(parent)                   // Llama al constructor de la clase base QDialog.
    , ui(new Ui::Clientes)               // Crea el puntero de la interfaz de usuario.
    , vectorClientes(vectorClientesRef)  // Inicializa la referencia al vector de clientes.
{
    ui->setupUi(this);                  // Configura la interfaz de usuario.
    this->setWindowTitle("Formulario de clientes");  // Establece el título de la ventana.
    initstylesheet();                   // Llama a la función para cargar el estilo (CSS).

    // Conecta el botón 'Aceptar' del cuadro de diálogo con el método de registro de cliente.
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Clientes::registrarCliente);
}

Clientes::~Clientes()
{
    delete ui;  // Libera la memoria utilizada por la interfaz de usuario.
}

// Métodos Getter y Setter para los atributos del cliente.
int Clientes::getIDcliente() const
{
    return idCliente;
}

void Clientes::setIDcliente(int idcliente)
{
    idCliente = idcliente;
}

QString Clientes::getNombre() const
{
    return Nombre;
}

void Clientes::setNombre(const QString &nombre)
{
    Nombre = nombre;
}

QString Clientes::getApellido() const
{
    return Apellido;
}

void Clientes::setApellido(const QString &apellido)
{
    Apellido = apellido;
}

int Clientes::getDni() const
{
    return Dni;
}

void Clientes::setDni(int dni)
{
    Dni = dni;
}

int Clientes::getEdad() const
{
    return Edad;
}

void Clientes::setEdad(int edad)
{
    Edad = edad;
}

int Clientes::getTelefono() const
{
    return Telefono;
}

void Clientes::setTelefono(int telefono)
{
    Telefono = telefono;
}

// Función para inicializar la hoja de estilo de la ventana.
void Clientes::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Ruta al archivo de estilos CSS.
    if (style.open(QFile::ReadOnly)) {  // Intenta abrir el archivo en modo solo lectura.
        QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el archivo CSS.
        this->setStyleSheet(stringEstilo);  // Aplica el estilo a la ventana.
    } else {
        qDebug() << "No se pudo cargar el archivo de estilo.";  // En caso de error al cargar el estilo.
    }
}

// Método que registra un cliente.
void Clientes::registrarCliente()
{
    QString filePath = QDir::currentPath() + "/clientes.csv";  // Ruta al archivo CSV donde se guardarán los clientes.

    // Verifica que todos los campos estén completos.
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() ||
        ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() ||
        ui->lineEdit_5->text().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Todos los campos deben ser completados.");
        return;  // Si algún campo está vacío, muestra una advertencia y termina la función.
    }

    // Crea un nuevo objeto Cliente con los datos del formulario.
    Clientes *cliente = new Clientes(vectorClientes, this);
    cliente->setIDcliente(ui->lineEdit->text().toInt());
    cliente->setNombre(ui->lineEdit_2->text());
    cliente->setApellido(ui->lineEdit_3->text());
    cliente->setDni(ui->lineEdit_4->text().toInt());
    cliente->setEdad(ui->spinBox->value());
    cliente->setTelefono(ui->lineEdit_5->text().toInt());

    // Agrega el cliente al vector de clientes.
    vectorClientes.push_back(cliente);

    // Guarda el cliente en el archivo CSV.
    guardarClienteEnCSV(filePath, *cliente);

    // Muestra un mensaje de confirmación.
    QMessageBox::information(this, "Cliente guardado", "Cliente registrado correctamente.");

    // Emite una señal para notificar que un nuevo cliente ha sido agregado.
    emit clienteAgregado(cliente->getIDcliente(), cliente->getNombre(), cliente->getApellido(),
                         cliente->getDni(), cliente->getEdad(), cliente->getTelefono());
}

// Función que lee los clientes desde el archivo CSV.
void Clientes::leerClientesDesdeArchivo()
{
    QString filePath = QDir::currentPath() + "/clientes.csv";  // Ruta al archivo CSV.
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // Abre el archivo para lectura.
        qDebug() << "Error al abrir el archivo:" << file.errorString();  // Si falla al abrirlo, muestra el error.
        return;
    }

    QTextStream in(&file);  // Prepara el flujo de texto para leer el archivo.
    vectorClientes.clear();  // Limpia el vector de clientes antes de cargar los nuevos datos.

    // Lee el archivo línea por línea.
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');  // Separa los campos de cada línea.

        // Verifica que la línea tenga el número correcto de campos.
        if (fields.size() == 6) {
            // Crea un objeto Cliente a partir de los datos leídos.
            Clientes *cliente = new Clientes(vectorClientes, this);
            cliente->setIDcliente(fields[0].toInt());
            cliente->setNombre(fields[1]);
            cliente->setApellido(fields[2]);
            cliente->setDni(fields[3].toInt());
            cliente->setEdad(fields[4].toInt());
            cliente->setTelefono(fields[5].toInt());

            // Agrega el cliente al vector.
            vectorClientes.push_back(cliente);
        }
    }

    file.close();  // Cierra el archivo después de leerlo.
}

// Función para guardar un cliente en el archivo CSV.
void Clientes::guardarClienteEnCSV(const QString &archivo, const Clientes &cliente)
{
    QFile file(archivo);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {  // Abre el archivo en modo append (agregar al final).
        qDebug() << "Error al abrir el archivo:" << file.errorString();  // Si no se puede abrir el archivo, muestra un error.
        return;
    }

    QTextStream out(&file);  // Prepara el flujo de salida para escribir en el archivo.
    out << cliente.getIDcliente() << ","  // Escribe los datos del cliente en formato CSV.
        << cliente.getNombre() << ","
        << cliente.getApellido() << ","
        << cliente.getDni() << ","
        << cliente.getEdad() << ","
        << cliente.getTelefono() << "\n";

    file.close();  // Cierra el archivo después de escribir los datos.
}

// Función para inicializar el archivo CSV con los encabezados si no existe.
void Clientes::inicializarCSV(const QString &archivo)
{
    QFile file(archivo);
    if (!file.exists()) {  // Verifica si el archivo ya existe.
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {  // Si no existe, lo crea.
            QTextStream out(&file);
            out << "ID,Nombre,Apellido,DNI,Edad,Telefono\n";  // Escribe los encabezados en el archivo CSV.
            file.close();  // Cierra el archivo después de escribir los encabezados.
        } else {
            qDebug() << "No se pudo inicializar el archivo:" << file.errorString();  // Muestra el error si no se puede abrir el archivo.
        }
    }
}
