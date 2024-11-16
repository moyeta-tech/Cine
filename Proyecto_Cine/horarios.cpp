#include "horarios.h"
#include "ui_horarios.h"

Horarios::Horarios(std::vector<Peliculas *> &VectorPeliculasRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Horarios)
    , VectorPeliculas(VectorPeliculasRef)
{
    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Horarios");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    for(const auto &peli : VectorPeliculas){
        ui->comboBox_peliculas->addItem(peli->getTitulo());
    }


}

Horarios::~Horarios()
{
    delete ui;
}

// GET Y SET DE HORA
QString Horarios::getHora()
{
    return Hora;
}

void Horarios::setHora(QString hora)
{
    Hora = hora;
}

// GET Y SET DE DIA

QString Horarios::getDia()
{
    return Dia;
}

void Horarios::setDia(QString dia)
{
    Dia = dia;
}


// HOJA DE ESTILOS
void Horarios::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
