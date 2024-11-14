#include "precios.h"
#include "cine.h"
#include "ui_precios.h"

Precios::Precios(QString tipoentrada, float preciobase, float descuento, QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::Precios),
    TipoEntrada(tipoentrada), PrecioBase(preciobase), Descuento(descuento)
{
    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Precios");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();
}


Precios::~Precios()
{
    delete ui;
}

// GET Y SET DE TIPOENTRADA
void Precios::setTipoEntrada(QString tipoentrada)
{
    TipoEntrada = tipoentrada;
}

QString Precios::getTipoEntrada()
{
    return TipoEntrada;
}


// GET Y SET DE PRECIOBASE
void Precios::setprecioBase(float preciobase)
{
    PrecioBase = preciobase;
}

float Precios::getprecioBase()
{
    return PrecioBase;
}

// GET Y SET DE DESCUENTO
void Precios::setDescuento(float descuento)
{
    Descuento = descuento;
}

float Precios::getDescuento()
{
    return Descuento;
}

// CALCULAR EL PRECIO FINAL
float Precios::calcularPrecio()
{
    float res = PrecioBase - Descuento;
    return res;
}

//Hoja de estilos
void Precios::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
