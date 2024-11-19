#include "venta.h"
#include "ui_venta.h"
#include "horarios.h"
#include "pago.h"
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

    // Establecemos el título de la ventana
    this->setWindowTitle("Paso 1: Selección de película y valor");

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // Actualizamos el combobox de películas para seleccionar
    for (const auto &peli : VectorPeliculas) {
        ui->comboBox_pelicula->addItem(peli->getTitulo());
    }

    // Conectar el evento de cambio de película seleccionada
    connect(ui->comboBox_pelicula, SIGNAL(currentIndexChanged(int)), this, SLOT(actualizarHorarios()));

    // Conectar el botón de continuar con la selección de asientos
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Venta::seleccionAsientos);
    connect(ui->Boton_continuar, &QPushButton::clicked, this, &Venta::accept);

    // Conectar los spinboxes para actualizar el costo
    connect(ui->spinBox_2d, &QSpinBox::valueChanged, this, &Venta::actualizarCosto);
    connect(ui->spinBox_3d, &QSpinBox::valueChanged, this, &Venta::actualizarCosto);

    // Conectar los botones de aplicar descuento
    connect(ui->Boton_2x1, &QPushButton::clicked, this, &Venta::aplicarDesc);
    connect(ui->Boton_25, &QPushButton::clicked, this, &Venta::aplicarDesc);
    connect(ui->Boton_10, &QPushButton::clicked, this, &Venta::aplicarDesc);

    // Mostrar horarios y fecha de la primera película
    if (!VectorPeliculas.empty()) {
        ui->comboBox_pelicula->setCurrentIndex(0);
        actualizarHorarios();
    }
}

Venta::~Venta()
{
    delete ui;
}

// Método para cargar el stylesheet
void Venta::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " << styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

// Método para actualizar los horarios y fecha de la película seleccionada
void Venta::actualizarHorarios()
{
    // Obtener el índice de la película seleccionada
    int indice = ui->comboBox_pelicula->currentIndex();
    if (indice < 0 || indice >= static_cast<int>(VectorPeliculas.size())) {
        QMessageBox::warning(this, "Error", "Película no válida seleccionada.");
        return;
    }

    // Obtener la película seleccionada
    Peliculas *peliculaSeleccionada = VectorPeliculas[indice];

    // Obtener horarios y días de la película seleccionada
    QList<QTime> horarios = peliculaSeleccionada->getHorarios();
    QDate dia = peliculaSeleccionada->getDia();

    // Limpiar los horarios previos
    ui->listWidget_horarios->clear();

    // Mostrar los horarios en la lista
    for (const QTime &horario : horarios) {
        ui->listWidget_horarios->addItem(horario.toString("hh:mm"));
    }

    // Mostrar la fecha del día
    ui->label_dia->setText("Día: " + dia.toString("dd/MM/yyyy"));
}

// Método para seleccionar asientos
void Venta::seleccionAsientos()
{
    if (ui->comboBox_pelicula->currentIndex() == -1 || ui->spinBox_2d->value() == 0 || ui->spinBox_3d->value() == 0 || ui->label_dia->text().isEmpty() || ui->listWidget_horarios->selectedItems().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Complete los campos vacíos por favor.");
        return;
    }

    // Obtener la fecha y hora seleccionadas
    QString diaSeleccionado = ui->label_dia->text(); // Ahora obtenemos el texto del QLabel
    QString horaSeleccionada = ui->listWidget_horarios->selectedItems().first()->text();
    Fecha = diaSeleccionado + " " + horaSeleccionada;

    // Abre el diálogo de asientos
    Asientos asientosDialog(this);
    if (asientosDialog.exec() == QDialog::Accepted) {
        // Después de cerrar Asientos, pasa datos a Pago
        QString metodo = "Tarjeta"; // Ejemplo
        float monto = costoTotal;
        QString fecha = Fecha; // Usa la fecha seleccionada
        Pago pagoDialog(metodo, monto, fecha, this);

        // Pasar los datos recolectados desde Asientos
        pagoDialog.setAsientos(asientosDialog.getAsientosSeleccionados().join(", ")); // Método para obtener los asientos
        pagoDialog.exec();
    }
}

// Método para actualizar el costo total
void Venta::actualizarCosto()
{
    int cantidad2D = ui->spinBox_2d->value();
    int cantidad3D = ui->spinBox_3d->value();

    double precio2D = 2000; // PRECIO DE ENTRADA 2D
    double precio3D = 2750; // PRECIO DE ENTRADA 3D

    costoTotal = (cantidad2D * precio2D) + (cantidad3D * precio3D);

    // Aplicar descuento
    if (descuentoActivo == "2x1") {
        int cant2DPagadas = cantidad2D / 2 + cantidad2D % 2; // 2D PAGA LA MITAD
        int cant3DPagadas = cantidad3D / 2 + cantidad3D % 2; // 3D PAGA LA MITAD
        costoTotal = (cant2DPagadas * precio2D) + (cant3DPagadas * precio3D);
    } else if (descuentoActivo == "Débito") {
        costoTotal *= 0.90; // APLICA UN 10% DE DESCUENTO
    } else if (descuentoActivo == "Crédito") {
        costoTotal *= 0.75; // APLICA UN DESCUENTO DE 25%
    }

    ui->label_9->setText(QString("Total: $%1").arg(QString::number(costoTotal, 'f', 2)));
}

// Método para aplicar descuento
void Venta::aplicarDesc()
{
    QPushButton *botonPresionado = qobject_cast<QPushButton *>(sender()); // IDENTIFICA AUTOMATICAMENTE QUE BOTON APRETAMOS

    if (botonPresionado == ui->Boton_2x1) {
        descuentoActivo = "2x1";
    } else if (botonPresionado == ui->Boton_25) {
        descuentoActivo = "Crédito";
    } else if (botonPresionado == ui->Boton_10) {
        descuentoActivo = "Débito";
    }

    actualizarCosto(); // SE LLAMA A LA FUNCION DE ACTUALIZAR EL TOTAL
}
