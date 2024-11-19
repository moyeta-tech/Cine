#include "verhistorial.h"
#include "ui_verhistorial.h"

verHistorial::verHistorial(std::vector<Venta *> &vectorHistorialRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::verHistorial)
    , vectorHistorial(vectorHistorialRef)
{
    ui->setupUi(this);

    //ESTABLECEMOS EL TITULO DE LA VENTANA
    this->setWindowTitle("Historial de ventas");
    // LLAMAMOS AL METODO PARA CARGAR LA HOJA DE ESTILOS
    initstylesheet();

    // CONFIGURAMOS LA TABLA VERCLIENTES PARA 2 COLUMNAS
    ui->tableWidget->setColumnCount(2);

    // DECLARAMOS QSTRINGLIST PARA LAS COLUMNAS

    QStringList encabezados;

    encabezados << "Tipo de Entrada" << "Total";

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);
}

verHistorial::~verHistorial()
{
    delete ui;
}

void verHistorial::initstylesheet(){
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

void verHistorial::cargarDatosTabla(const QString &fecha, double monto){
    int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fecha));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(monto)));
    }

