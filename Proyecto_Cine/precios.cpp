#include "precios.h"
#include "cine.h"
#include "ui_precios.h"

// Constructor de la clase Precios
Precios::Precios(QString tipoentrada, float preciobase, float descuento, QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::Precios),
    TipoEntrada(tipoentrada), PrecioBase(preciobase), Descuento(descuento)
{
    ui->setupUi(this);  // Configura la interfaz de usuario

    // Establece el título de la ventana
    this->setWindowTitle("Precios");

    // Llama al slot para cargar el stylesheet
    initstylesheet();
}

// Destructor que limpia los recursos
Precios::~Precios()
{
    delete ui;  // Elimina la interfaz de usuario
}

// GET Y SET DE TIPOENTRADA
void Precios::setTipoEntrada(QString tipoentrada)
{
    TipoEntrada = tipoentrada;  // Establece el tipo de entrada
}

QString Precios::getTipoEntrada()
{
    return TipoEntrada;  // Devuelve el tipo de entrada
}

// GET Y SET DE PRECIOBASE
void Precios::setprecioBase(float preciobase)
{
    PrecioBase = preciobase;  // Establece el precio base
}

float Precios::getprecioBase()
{
    return PrecioBase;  // Devuelve el precio base
}

// GET Y SET DE DESCUENTO
void Precios::setDescuento(float descuento)
{
    Descuento = descuento;  // Establece el descuento
}

float Precios::getDescuento()
{
    return Descuento;  // Devuelve el descuento
}

// CALCULAR EL PRECIO FINAL
float Precios::calcularPrecio()
{
    float res = PrecioBase - Descuento;  // Calcula el precio final con descuento
    return res;  // Devuelve el precio final
}

// Hoja de estilos
void Precios::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Ruta del archivo de estilo
    bool styleOK = style.open(QFile::ReadOnly);  // Intenta abrir el archivo de estilo
    qDebug() << "Apertura de archivos: " << styleOK;  // Mensaje de depuración
    QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el contenido del archivo CSS
    this->setStyleSheet(stringEstilo);  // Aplica el estilo a la ventana
}
