#include "pago.h"
#include "ui_pago.h"

Pago::Pago(QString metodo, float monto, QString fecha, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Pago)
{
    ui->setupUi(this);

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

// GET Y SET DE METODO
QString Pago::getMetodo()
{
    return Metodo;
}

void Pago::setMetodo(QString metodo)
{
    Metodo = metodo;
}

// GET Y SET DE MONTO

float Pago::getMonto()
{
    return Monto;
}

void Pago::setMonto(float monto)
{
    Monto = monto;
}

// GET Y SET DE FECHA

QString Pago::getFecha()
{
    return Fecha;
}

void Pago::setFecha(QString fecha)
{
    Fecha = fecha;
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
