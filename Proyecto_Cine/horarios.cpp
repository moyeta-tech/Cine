#include "horarios.h"
#include "ui_horarios.h"

Horarios::Horarios(std::vector<Peliculas*> &VectorPeliculasRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Horarios)
    , VectorPeliculas(VectorPeliculasRef)
{
    ui->setupUi(this);

    // Establecemos el título de la ventana
    this->setWindowTitle("Horarios");

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();

    // Rellenamos el combobox con los títulos de las películas
    for (const auto &peli : VectorPeliculas) {
        ui->comboBox_peliculas->addItem(peli->getTitulo());
    }

    // Conectamos el evento de cambio en el QComboBox
    connect(ui->comboBox_peliculas, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Horarios::mostrarHorariosYDia);
}

Horarios::~Horarios()
{
    delete ui;
}

void Horarios::mostrarHorariosYDia()
{
    // Obtener el índice seleccionado
    int indice = ui->comboBox_peliculas->currentIndex();
    if (indice < 0 || indice >= static_cast<int>(VectorPeliculas.size())) {
        QMessageBox::warning(this, "Error", "Película no válida seleccionada.");
        return;
    }


    // Obtener la película seleccionada
    Peliculas *peliculaSeleccionada = VectorPeliculas[indice];

    // Obtener horarios y días
    QList<QTime> horarios = peliculaSeleccionada->getHorarios();
    QDate dia = peliculaSeleccionada->getDia();

    // Limpiar listas previas (si se utiliza un QListWidget)
    ui->listWidget_horarios->clear();

    // Mostrar horarios en la lista
    for (const QTime &horario : horarios) {
        ui->listWidget_horarios->addItem(horario.toString("hh:mm"));
    }

    // Mostrar día
    ui->label_dia->setText("Día: " + dia.toString("dd/MM/yyyy"));
}

void Horarios::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivo de estilos: " << styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
