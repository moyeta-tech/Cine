#include "pago.h"
#include "ui_pago.h"

// Constructor de la clase Pago
// Inicializa la ventana de pago con los parámetros: método de pago, monto total y fecha.
Pago::Pago(QString metodo, float monto, QString fecha, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Pago)
{
    ui->setupUi(this);  // Configura la interfaz gráfica (UI)

    Metodo = metodo;    // Almacena el método de pago
    Monto = monto;      // Almacena el monto total
    Fecha = fecha;      // Almacena la fecha de la transacción

    // Establece el título de la ventana
    this->setWindowTitle("Paso 3: Seleccion metodo de pago");

    // Llama al método para cargar el archivo de estilo (CSS)
    initstylesheet();

    // Introduce los métodos de pago en el QComboBox
    ui->comboBox_medios->addItem("Efectivo");
    ui->comboBox_medios->addItem("Tarjeta de crédito");
    ui->comboBox_medios->addItem("Tarjeta de débito");

    // Conecta el botón de finalizar con el slot que procesa la compra
    connect(ui->Boton_finalizar, &QPushButton::clicked, this, &Pago::finalizarCompra);
}

// Constructor vacío, probablemente para crear un objeto sin inicializar al principio
Pago::Pago() {

}

// Destructor de la clase, elimina la UI
Pago::~Pago()
{
    delete ui;  // Libera la memoria ocupada por la interfaz
}

// Métodos getter y setter para los atributos privados

QString Pago::getMetodo()
{
    return Metodo;  // Devuelve el método de pago seleccionado
}

void Pago::setMetodo(QString metodo)
{
    Metodo = metodo;  // Establece el método de pago
}

double Pago::getMonto() const
{
    return Monto;  // Devuelve el monto total de la compra
}

void Pago::setMonto(double monto)
{
    Monto = monto;  // Establece el monto total de la compra
}

QString Pago::getFecha()
{
    return Fecha;  // Devuelve la fecha de la transacción
}

void Pago::setFecha(QString fecha)
{
    Fecha = fecha;  // Establece la fecha de la transacción
}

// Método que simula la finalización de la compra
// Al ser llamado, se cierra el diálogo y marca el estado como "aceptado"
bool Pago::finalizarCompra()
{
    this->accept();  // Cierra el diálogo y devuelve QDialog::Accepted
    return true;     // Indica que la compra se ha finalizado correctamente
}

// Método para cargar el archivo de estilos (CSS) para la interfaz
void Pago::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Ruta al archivo de estilo
    bool styleOK = style.open(QFile::ReadOnly);  // Abre el archivo de estilo en modo solo lectura
    qDebug() << "Apertura de archivos: " << styleOK;  // Imprime en el log si el archivo se abrió correctamente
    QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el contenido del archivo CSS
    this->setStyleSheet(stringEstilo);  // Aplica el estilo al diálogo
}

// Método para establecer los asientos seleccionados
void Pago::setAsientos(const QString& asientos)
{
    AsientosSeleccionados = asientos;  // Almacena los asientos seleccionados por el usuario
}
