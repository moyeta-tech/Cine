#include "venta.h"
#include "ui_venta.h"
#include "horarios.h"
#include "pago.h"
#include "asientos.h"

Venta::Venta(std::vector<Peliculas *> VectorPeliculasRef, QString fecha, int cantasientos, Clientes *cliente, Horarios *horario, Pago *pago, QWidget *parent)
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

    // Establecemos el título de la ventana
    this->setWindowTitle("Paso 1: Selección de película y valor");

    // Inicializamos estilos
    initstylesheet();

    // Rellenar el comboBox con las películas
    for (const auto &peli : VectorPeliculas) {
        ui->comboBox_pelicula->addItem(peli->getTitulo());
    }

    // Conectar eventos
    connect(ui->comboBox_pelicula, &QComboBox::currentIndexChanged, this, &Venta::actualizarHorarios);
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Venta::seleccionAsientos);
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Venta::accept);

    connect(ui->radioButton_2d, &QRadioButton::toggled, this, &Venta::actualizarCosto);
    connect(ui->radioButton_3d, &QRadioButton::toggled, this, &Venta::actualizarCosto);
    connect(ui->spinBox_cantidad, SIGNAL(valueChanged(int)), this, SLOT(actualizarCosto()));

    // Conectar botones de descuento
    connect(ui->Boton_10, &QPushButton::clicked, this, &Venta::aplicarDescuento10);
    connect(ui->Boton_25, &QPushButton::clicked, this, &Venta::aplicarDescuento25);
    connect(ui->Boton_2x1, &QPushButton::clicked, this, &Venta::aplicarDescuento2x1);

    // Inicializar valores
    ui->radioButton_2d->setChecked(true); // Por defecto, selecciona 2D
    ui->spinBox_cantidad->setValue(1); // Cantidad inicial
    actualizarCosto(); // Actualiza el costo inicial

    if (!VectorPeliculas.empty()) {
        ui->comboBox_pelicula->setCurrentIndex(0);
        actualizarHorarios();
    }
}

Venta::Venta(){}

Venta::~Venta()
{
    delete ui;
}

QString Venta::getFecha() const{  // GET Y SET DE FECHA
    return Fecha;
}

void Venta::setFecha(QString fecha){
    Fecha = fecha;
}

Pago *Venta::getPago(){
    return pago;
}

void Venta::setPago(Pago *pago){
    pago = pago;
}

void Venta::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    if (style.open(QFile::ReadOnly)) {
        this->setStyleSheet(QString::fromLatin1(style.readAll()));
    }
}

void Venta::actualizarHorarios()
{
    int indice = ui->comboBox_pelicula->currentIndex();
    qDebug() << "Indice: " << indice;
    if (indice < 0 || indice >= static_cast<int>(VectorPeliculas.size())) {
        qDebug() << "El indice esta fuera de rango";
        QMessageBox::warning(this, "Error", "Película no válida seleccionada.");
        return;
    }

    Peliculas *peliculaSeleccionada = VectorPeliculas[indice];
    QList <QTime> horarios = peliculaSeleccionada->getHorarios();
    qDebug() << "Horarios dispo: " << horarios;

    ui->listWidget_horarios->clear();


    if(horarios.isEmpty()){
        QMessageBox::information(this, "Aviso", "No hay horarios disponibles");
        return;
    }

    for (const QTime &horario : horarios) {
            ui->listWidget_horarios->addItem(horario.toString("HH:mm"));
    }

            QDate dia = peliculaSeleccionada->getDia();
            ui->label_dia->setText("Día: " + dia.toString("dd/MM/yyyy"));
}

void Venta::seleccionAsientos() {
    if (ui->comboBox_pelicula->currentIndex() == -1 ||
        ui->spinBox_cantidad->value() == 0 ||
        ui->label_dia->text().isEmpty() ||
        ui->listWidget_horarios->selectedItems().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Complete los campos vacíos por favor.");
        return;
    }

    QString diaSeleccionado = ui->label_dia->text();
    QString horaSeleccionada = ui->listWidget_horarios->selectedItems().first()->text();
    Fecha = diaSeleccionado + " " + horaSeleccionada;

    Asientos asientosDialog(this);
    asientosDialog.setLimiteAsientos(ui->spinBox_cantidad->value()); // Pasa el límite
    if (asientosDialog.exec() == QDialog::Accepted) {
        QString metodo = "Tarjeta";
        float monto = costoTotal;
        QString fecha = Fecha;
        Pago pagoDialog(metodo, monto, fecha, this);
        pagoDialog.setAsientos(asientosDialog.getAsientosSeleccionados().join(", "));
        pagoDialog.exec();
    }
}


void Venta::actualizarCosto()
{
    int cantidad = ui->spinBox_cantidad->value();
    double precio2D = 2000; // Precio 2D
    double precio3D = 2750; // Precio 3D

    // Calcula el costo base
    if (ui->radioButton_2d->isChecked()) {
        costoBase = cantidad * precio2D;
    } else if (ui->radioButton_3d->isChecked()) {
        costoBase = cantidad * precio3D;
    }

    // Si no hay descuento aplicado, actualiza el costo total
    if (!descuentoAplicado) {
        costoTotal = costoBase;
    }

    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));
}


// Función para aplicar descuento del 10%
void Venta::aplicarDescuento10()
{
    // Si ya se había aplicado un descuento, restaura el costo base
    if (descuentoAplicado) {
        costoTotal = costoBase; // Restaura el precio base
    }

    // Aplica el descuento del 10%
    costoTotal *= 0.90;
    descuentoAplicado = true; // Marca que se ha aplicado el descuento
    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));
}


// Función para aplicar descuento del 25%
void Venta::aplicarDescuento25()
{
    // Si ya se había aplicado un descuento, restaura el costo base
    if (descuentoAplicado) {
        costoTotal = costoBase; // Restaura el precio base
    }

    // Aplica el descuento del 25%
    costoTotal *= 0.75;
    descuentoAplicado = true; // Marca que se ha aplicado el descuento
    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));
}


// Función para aplicar descuento 2x1
void Venta::aplicarDescuento2x1()
{
    // Si ya se había aplicado un descuento, restaura el costo base
    if (descuentoAplicado) {
        costoTotal = costoBase; // Restaura el precio base
    }

    int cantidad = ui->spinBox_cantidad->value();
    if (cantidad >= 2) {
        int cantidadDescuento = cantidad / 2 + (cantidad % 2); // Compra 2, obtén 1
        costoTotal = cantidadDescuento * (ui->radioButton_2d->isChecked() ? 2000 : 2750); // Asegúrate de que el precio esté actualizado
    }
    descuentoAplicado = true; // Marca que se ha aplicado el descuento
    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));
}


void Venta::resetearDescuento()
{
    descuentoAplicado = false;
    costoTotal = costoBase; // Restaura el precio base
    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));
}


void Venta::on_Boton_continuar_clicked()
{
    QString fecha = ui->label_dia->text();
    QString total = ui->label_9->text().remove("Total: $");
    double monto = total.toDouble();

    emit ventaConfirmada(fecha, monto);
}



