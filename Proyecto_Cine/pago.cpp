#include "pago.h"
#include "ui_pago.h"

Pago::Pago(QString metodo, float monto, QString fecha, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Pago)
{
    ui->setupUi(this);

    Metodo = metodo;
    Monto = monto;
    Fecha = fecha;

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Paso 3: Seleccion metodo de pago");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // INTRODUCIMOS LOS METODOS DE PAGO EN EL COMBOBOX
    ui->comboBox_medios->addItem("Efectivo");
    ui->comboBox_medios->addItem("Tarjeta de crédito");
    ui->comboBox_medios->addItem("Tarjeta de débito");


    //Conectamos los botones con los slots
    connect(ui->Boton_finalizar, &QPushButton::clicked, this, &Pago::finalizarCompra);
}

Pago::~Pago()
{
    delete ui;
}


QString Pago::getMetodo()
{
    return Metodo;  // Usamos 'Metodo' en lugar de 'metodoPago'
}

void Pago::setMetodo(QString metodo)
{
    Metodo = metodo;  // Usamos 'Metodo' en lugar de 'metodoPago'
}

float Pago::getMonto()
{
    return Monto;  // Usamos 'Monto' en lugar de 'montoTotal'
}

void Pago::setMonto(float monto)
{
    Monto = monto;  // Usamos 'Monto' en lugar de 'montoTotal'
}

QString Pago::getFecha()
{
    return Fecha;  // Usamos 'Fecha' en lugar de 'fechaPago'
}

void Pago::setFecha(QString fecha)
{
    Fecha = fecha;  // Usamos 'Fecha' en lugar de 'fechaPago'
}

void Pago::finalizarCompra()
{
    this->accept();  // Cierra el diálogo y devuelve QDialog::Accepted
}

// HOJA DE ESTILOS
void Pago::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

void Pago::setAsientos(const QString& asientos)
{
    AsientosSeleccionados = asientos;
    ui->label_asiento->setText("Asientos seleccionados: " + asientos);

}
