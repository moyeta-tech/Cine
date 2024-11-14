#include "verclientes.h"
#include "ui_verclientes.h"

VerClientes::VerClientes(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerClientes)
{
    ui->setupUi(this);

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();
}

VerClientes::~VerClientes()
{
    delete ui;
}

void VerClientes::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
