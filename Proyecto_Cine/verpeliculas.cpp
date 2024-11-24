#include "verpeliculas.h"
#include "ui_verpeliculas.h"

VerPeliculas::VerPeliculas(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerPeliculas)
{
    ui->setupUi(this);

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();
}

VerPeliculas::~VerPeliculas()
{
    delete ui;
}

void VerPeliculas::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
