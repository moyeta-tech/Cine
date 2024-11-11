
#include "precios.h"
#include "ui_precios.h"

precios::precios(QString tipoentrada, float preciobase, float descuento, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::precios)
{
    ui->setupUi(this);
}

precios::~precios()
{
    delete ui;
}

// GET Y SET DE TIPOENTRADA

QString precios::getTipoEntrada(){
    return TipoEntrada;
}

void precios::setTipoEntrada(QString tipoentrada){
    TipoEntrada = tipoentrada;
}

// GET Y SET DE PRECIOBASE

float precios::getprecioBase(){
    return PrecioBase;
}

void precios::setprecioBase(float preciobase){
    PrecioBase = preciobase;
}

// GET Y SET DE DESCUENTO

float precios::getDescuento(){
    return Descuento;
}

void precios::setDescuento(float descuento){
    Descuento = descuento;
}
// CALCULAR EL PRECIO FINAL
float precios::calcularPrecio(){
    float res = PrecioBase - Descuento;
    return res;
}
