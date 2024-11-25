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
    this->setWindowTitle("Paso 1: Selección de película y valor");  // Establece el título de la ventana

    // Inicializamos estilos
    initstylesheet();  // Aplica el estilo CSS personalizado

    // Rellenar el comboBox con las películas
    for (const auto &peli : VectorPeliculas) {
        ui->comboBox_pelicula->addItem(peli->getTitulo());  // Agrega los títulos de las películas al combobox
    }

    // Conectar eventos
    connect(ui->comboBox_pelicula, &QComboBox::currentIndexChanged, this, &Venta::actualizarHorarios);  // Cambia horarios al seleccionar película
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Venta::seleccionAsientos);  // Continúa con la selección de asientos
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Venta::accept);  // Acepta la venta

    connect(ui->radioButton_2d, &QRadioButton::toggled, this, &Venta::actualizarCosto);  // Cambia el costo si se selecciona 2D
    connect(ui->radioButton_3d, &QRadioButton::toggled, this, &Venta::actualizarCosto);  // Cambia el costo si se selecciona 3D
    connect(ui->spinBox_cantidad, SIGNAL(valueChanged(int)), this, SLOT(actualizarCosto()));  // Actualiza costo al cambiar cantidad de entradas

    // Conectar botones de descuento
    connect(ui->Boton_10, &QPushButton::clicked, this, &Venta::aplicarDescuento10);  // Aplica descuento 10%
    connect(ui->Boton_25, &QPushButton::clicked, this, &Venta::aplicarDescuento25);  // Aplica descuento 25%
    connect(ui->Boton_2x1, &QPushButton::clicked, this, &Venta::aplicarDescuento2x1);  // Aplica descuento 2x1

    // Inicializar valores
    ui->radioButton_2d->setChecked(true);  // Por defecto, selecciona 2D
    ui->spinBox_cantidad->setValue(1);  // Cantidad inicial de entradas
    actualizarCosto();  // Actualiza el costo inicial

    if (!VectorPeliculas.empty()) {
        ui->comboBox_pelicula->setCurrentIndex(0);  // Selecciona la primera película
        actualizarHorarios();  // Actualiza los horarios disponibles
    }
}

Venta::Venta(){}

Venta::~Venta()
{
    delete ui;  // Libera la memoria al destruir el objeto
}

QString Venta::getFecha() const{  // GET Y SET DE FECHA
    return Fecha;  // Retorna la fecha de la venta
}

void Venta::setFecha(QString fecha){
    Fecha = fecha;  // Establece la fecha de la venta
}

Pago *Venta::getPago(){
    return pago;  // Retorna el objeto de pago
}

void Venta::setPago(Pago *pago){
    pago = pago;  // Establece el objeto de pago
}

void Venta::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Abre el archivo de estilo
    if (style.open(QFile::ReadOnly)) {
        this->setStyleSheet(QString::fromLatin1(style.readAll()));  // Aplica el estilo
    }
}

void Venta::actualizarHorarios()
{
    int indice = ui->comboBox_pelicula->currentIndex();  // Obtiene el índice de la película seleccionada
    qDebug() << "Indice: " << indice;
    if (indice < 0 || indice >= static_cast<int>(VectorPeliculas.size())) {
        qDebug() << "El indice esta fuera de rango";  // Verifica si el índice es válido
        QMessageBox::warning(this, "Error", "Película no válida seleccionada.");  // Muestra un mensaje de error si el índice es inválido
        return;
    }

    Peliculas *peliculaSeleccionada = VectorPeliculas[indice];  // Obtiene la película seleccionada
    QList <QTime> horarios = peliculaSeleccionada->getHorarios();  // Obtiene los horarios de la película seleccionada
    qDebug() << "Horarios dispo: " << horarios;

    ui->listWidget_horarios->clear();  // Limpia la lista de horarios

    if(horarios.isEmpty()){
        QMessageBox::information(this, "Aviso", "No hay horarios disponibles");  // Muestra un mensaje si no hay horarios disponibles
        return;
    }

    for (const QTime &horario : horarios) {  // Añade cada horario disponible a la lista
        ui->listWidget_horarios->addItem(horario.toString("HH:mm"));
    }

    QDate dia = peliculaSeleccionada->getDia();  // Obtiene la fecha de la película
    ui->label_dia->setText("Día: " + dia.toString("dd/MM/yyyy"));  // Muestra el día en el label
}

void Venta::seleccionAsientos() {
    if (ui->comboBox_pelicula->currentIndex() == -1 ||
        ui->spinBox_cantidad->value() == 0 ||
        ui->label_dia->text().isEmpty() ||
        ui->listWidget_horarios->selectedItems().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Complete los campos vacíos por favor.");  // Verifica que todos los campos estén completos
        return;
    }

    QString diaSeleccionado = ui->label_dia->text();  // Obtiene el día seleccionado
    QString horaSeleccionada = ui->listWidget_horarios->selectedItems().first()->text();  // Obtiene la hora seleccionada
    Fecha = diaSeleccionado + " " + horaSeleccionada;  // Establece la fecha y hora

    Asientos asientosDialog(this);  // Crea el objeto para seleccionar los asientos
    asientosDialog.setLimiteAsientos(ui->spinBox_cantidad->value());  // Pasa el límite de asientos
    if (asientosDialog.exec() == QDialog::Accepted) {
        QString metodo = "Tarjeta";  // Método de pago seleccionado
        float monto = costoTotal;  // Monto total de la compra
        QString fecha = Fecha;  // Fecha de la venta
        Pago pagoDialog(metodo, monto, fecha, this);  // Crea el objeto de pago
        pagoDialog.setAsientos(asientosDialog.getAsientosSeleccionados().join(", "));  // Asientos seleccionados
        pagoDialog.exec();  // Muestra el diálogo de pago
    }
}

void Venta::actualizarCosto()
{
    int cantidad = ui->spinBox_cantidad->value();  // Obtiene la cantidad de entradas
    double precio2D = 2000;  // Precio de entrada 2D
    double precio3D = 2750;  // Precio de entrada 3D

    // Calcula el costo base
    if (ui->radioButton_2d->isChecked()) {
        costoBase = cantidad * precio2D;  // Calcula el costo para 2D
    } else if (ui->radioButton_3d->isChecked()) {
        costoBase = cantidad * precio3D;  // Calcula el costo para 3D
    }

    // Si no hay descuento aplicado, actualiza el costo total
    if (!descuentoAplicado) {
        costoTotal = costoBase;  // Asigna el costo base
    }

    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));  // Muestra el costo total actualizado
}

// Función para aplicar descuento del 10%
void Venta::aplicarDescuento10()
{
    // Si ya se había aplicado un descuento, restaura el costo base
    if (descuentoAplicado) {
        costoTotal = costoBase;  // Restaura el costo base
    }

    // Aplica el descuento del 10%
    costoTotal *= 0.90;  // Aplica el 10% de descuento
    descuentoAplicado = true;  // Marca que se ha aplicado el descuento
    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));  // Muestra el nuevo total
}

// Función para aplicar descuento del 25%
void Venta::aplicarDescuento25()
{
    // Si ya se había aplicado un descuento, restaura el costo base
    if (descuentoAplicado) {
        costoTotal = costoBase;  // Restaura el costo base
    }

    // Aplica el descuento del 25%
    costoTotal *= 0.75;  // Aplica el 25% de descuento
    descuentoAplicado = true;  // Marca que se ha aplicado el descuento
    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));  // Muestra el nuevo total
}

// Función para aplicar descuento 2x1
void Venta::aplicarDescuento2x1()
{
    // Si ya se había aplicado un descuento, restaura el costo base
    if (descuentoAplicado) {
        costoTotal = costoBase;  // Restaura el costo base
    }

    int cantidad = ui->spinBox_cantidad->value();  // Obtiene la cantidad de entradas
    if (cantidad >= 2) {
        int cantidadDescuento = cantidad / 2 + (cantidad % 2);  // Compra 2, obtén 1
        costoTotal = cantidadDescuento * (ui->radioButton_2d->isChecked() ? 2000 : 2750);  // Calcula el costo con descuento
    }
    descuentoAplicado = true;  // Marca que se ha aplicado el descuento
    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));  // Muestra el nuevo total
}

void Venta::resetearDescuento()
{
    descuentoAplicado = false;  // Restablece el estado del descuento
    costoTotal = costoBase;  // Restaura el precio base
    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));  // Muestra el costo total original
}

void Venta::on_Boton_continuar_clicked()
{
    QString fecha = ui->label_dia->text();  // Obtiene la fecha seleccionada
    QString total = ui->label_9->text().remove("Total: $");  // Obtiene el monto total
    double monto = total.toDouble();  // Convierte el monto a tipo double

    emit ventaConfirmada(fecha, monto);  // Emite la señal de confirmación de venta
}
