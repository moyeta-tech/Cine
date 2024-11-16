#include "venta.h"
#include "ui_venta.h"

#include "asientos.h"

Venta::Venta(std::vector<Peliculas *> &VectorPeliculasRef, QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, Pago *pago, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Venta)
    ,
    Fecha(fecha)
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

void Venta::seleccionAsientos()
{
    Asientos dialog(this);
    dialog.exec();
}

// AL PRESIONAR BOTON CONTINUAR, TERMINAR LA OPERACION DE VENTA Y MOSTRAR LA INFORMACION DEL CLIENTE HACIA EL MISMO, SE CERRARÁ

void Venta::on_Boton_continuar_clicked()
{
    Venta *finalizar = new Venta(VectorPeliculas,Fecha, cantAsientos, cliente, horario, pago, this);
    finalizar->accept();
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
