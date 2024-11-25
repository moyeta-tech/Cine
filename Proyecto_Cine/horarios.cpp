#include "horarios.h"
#include "ui_horarios.h"

// Constructor de la clase Horarios
Horarios::Horarios(std::vector<Peliculas*> &VectorPeliculasRef, QWidget *parent)
    : QDialog(parent)  // Llama al constructor base QDialog
    , ui(new Ui::Horarios)  // Inicializa la interfaz de usuario a partir de la definición en el archivo .ui
    , VectorPeliculas(VectorPeliculasRef)  // Inicializa el vector de películas pasado como referencia
{
    ui->setupUi(this);  // Configura la interfaz de usuario de acuerdo con el archivo .ui

    // Establecemos el título de la ventana
    this->setWindowTitle("Horarios");

    // Llamamos al slot para cargar el stylesheet (hoja de estilos)
    initstylesheet();

    // Rellenamos el combobox con los títulos de las películas
    // Iteramos sobre el vector de películas y añadimos cada título al QComboBox
    for (const auto &peli : VectorPeliculas) {
        ui->comboBox_peliculas->addItem(peli->getTitulo());
    }

    // Conectamos el evento de cambio de selección en el QComboBox con el slot mostrarHorariosYDia
    connect(ui->comboBox_peliculas, &QComboBox::currentIndexChanged,
            this, &Horarios::mostrarHorariosYDia);

    // SELECCIONAMOS UN ÍNDICE POR DEFECTO Y MOSTRAMOS LOS DATOS CON "mostrarHorariosYDia();"
    // Si hay películas en el vector, seleccionamos la primera película y mostramos sus horarios
    if (!VectorPeliculas.empty()) {
        ui->comboBox_peliculas->setCurrentIndex(0);  // Establece la primera película como seleccionada por defecto
        mostrarHorariosYDia();  // Llama al método para mostrar los horarios y el día de la película seleccionada
    }
}

// Destructor de la clase Horarios
Horarios::~Horarios()
{
    delete ui;  // Libera la memoria utilizada por la interfaz de usuario
}

// Método para mostrar los horarios y el día de la película seleccionada
void Horarios::mostrarHorariosYDia()
{
    // Obtener el índice de la película seleccionada en el QComboBox
    int indice = ui->comboBox_peliculas->currentIndex();

    // Validamos que el índice seleccionado sea válido
    if (indice < 0 || indice >= static_cast<int>(VectorPeliculas.size())) {
        // Si el índice es inválido, mostramos un mensaje de advertencia
        QMessageBox::warning(this, "Error", "Película no válida seleccionada.");
        return;  // Terminamos la ejecución del método
    }

    // Obtener la película seleccionada a partir del índice
    Peliculas *peliculaSeleccionada = VectorPeliculas[indice];

    // Obtener los horarios y el día de la película seleccionada
    QList<QTime> horarios = peliculaSeleccionada->getHorarios();
    QDate dia = peliculaSeleccionada->getDia();

    // Limpiamos la lista de horarios (si existe una lista previa)
    ui->listWidget_horarios->clear();

    // Iteramos sobre los horarios y los mostramos en el QListWidget
    for (const QTime &horario : horarios) {
        qDebug() << "Agregando horario:" << horario.toString("HH:mm");  // Imprimimos el horario en formato HH:mm para depuración
        ui->listWidget_horarios->addItem(horario.toString("HH:mm"));  // Añadimos el horario a la lista
    }

    // Mostramos el día de la película seleccionada en el QLabel
    ui->label_dia->setText("Día: " + dia.toString("dd/MM/yyyy"));
}

// Método para inicializar el estilo de la ventana
void Horarios::initstylesheet()
{
    // Abrimos el archivo de estilos que se encuentra en los recursos
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");

    // Intentamos abrir el archivo de estilos en modo solo lectura
    bool styleOK = style.open(QFile::ReadOnly);

    // Imprimimos en consola si el archivo se abrió correctamente
    qDebug() << "Apertura de archivo de estilos: " << styleOK;

    // Leemos el contenido del archivo de estilos
    QString stringEstilo = QString::fromLatin1(style.readAll());

    // Aplicamos el estilo a la ventana usando el contenido del archivo
    this->setStyleSheet(stringEstilo);
}
