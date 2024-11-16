#include "venta.h"
#include "ui_venta.h"

#include "asientos.h"

Venta::Venta(std::vector<Peliculas *> &VectorPeliculasRef, QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, Pago *pago, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Venta)
    , Fecha(fecha)
    , cantAsientos(cantasientos)
    , cliente(cliente)
    , horario(horario)
    , pago(pago)
    , VectorPeliculas(VectorPeliculasRef)

{
    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Paso 1: Seleccion de prelicula y valor");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // ACTUALIZAMOS EL COMBOBOX DE PELICULAS PARA SELECCIONAR
    for(const auto &peli : VectorPeliculas){
       ui->comboBox_pelicula->addItem(peli->getTitulo());
    }

    //Boton para seleccionar los asientos
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Venta::seleccionAsientos);
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Venta::accept);

    connect(ui->Boton_2x1, &QPushButton::clicked, this, &Venta::aplicarDesc);
    connect(ui->Boton_25, &QPushButton::clicked, this, &Venta::aplicarDesc);
    connect(ui->Boton_10, &QPushButton::clicked, this, &Venta::aplicarDesc);
}

Venta::~Venta()
{
    delete ui;
}

// GET Y SET DE FECHA

QString Venta::getFecha()
{
    return Fecha;
}

void Venta::setFecha(QString fecha)
{
    Fecha = fecha;
}

// GET Y SET DE CANTASIENTOS

int Venta::getcantAsientos()
{
    return cantAsientos;
}

void Venta::setcantAsientos(int cantasientos)
{
    cantAsientos = cantasientos;
}

// GET Y SET DE CLIENTE

Clientes *Venta::getCliente()
{
    return cliente;
}

void Venta::setCliente(Clientes *cliente)
{
    this->cliente = cliente;
}

// GET Y SET DE HORARIO

Horarios *Venta::getHorario()
{
    return horario;
}

void Venta::setHorario(Horarios *horario)
{
    this->horario = horario;
}

// GET Y SET DE PAGO

Pago *Venta::getPago()
{
    return pago;
}

void Venta::setPago(Pago *pago)
{
    this->pago = pago;
}

// Método para seleccionar asientos
void Venta::seleccionAsientos()
{
    // Abre el diálogo de asientos
    Asientos dialog(this);
    dialog.exec();

    // Después de seleccionar los asientos, continua con la venta
    Venta *finalizar = new Venta(VectorPeliculas, Fecha, cantAsientos, cliente, horario, pago, this);
    finalizar->accept();  // Termina la operación de venta y muestra la información
}

void Venta::actualizarCosto(){
    int cantidad2D = ui->spinBox_2d->value();
    int cantidad3D = ui->spinBox_3d->value();

    double precio2D = 2000; // PRECIO DE ENTRADA 2D
    double precio3D = 2750; // PRECIO DE ENTRADA 3D

    costoTotal = (cantidad2D * precio2D) + (cantidad3D * precio3D);

    // APLICAMOS DESCUENTO O 2x1

    if(descuentoActivo == "2x1"){
        int cant2DPagadas = cantidad2D / 2 + cantidad2D % 2; // 2D PAGA LA MITAD
        int cant3DPagadas = cantidad3D / 2 + cantidad3D % 2; // 3D PAGA LA MITAD
        costoTotal = (cant2DPagadas * precio2D) + (cant3DPagadas * precio3D);
    } else if(descuentoActivo == "Débito"){
        costoTotal *= 0.90; // APLICA UN 10% DE DESCUENTO
    } else if(descuentoActivo == "Crédito"){
        costoTotal *= 0.75; // APLICA UN DESCUENTO DE 25%
    }

    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));
}

void Venta::aplicarDesc(){
    QPushButton *botonPresionado = qobject_cast<QPushButton *>(sender());

    if(botonPresionado == ui->Boton_2x1){
        descuentoActivo = "2x1";
    } else if(botonPresionado == ui->Boton_25){
        descuentoActivo = "Crédito";
    } else if(botonPresionado == ui->Boton_10){
        descuentoActivo = "Débito";
    }

    actualizarCosto();
}

// HOJA DE ESTILOS
void Venta::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
