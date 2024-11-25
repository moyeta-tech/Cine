#include "verhistorial.h"
#include "ui_verhistorial.h"

verHistorial::verHistorial(std::vector<Pago* > &vectorPagoRef, std::vector<Venta *> &vectorHistorialRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::verHistorial)
    , vectorHistorial(vectorHistorialRef)
    , vectorPago(vectorPagoRef)
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

    encabezados << "Fecha" << "Monto";

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

void verHistorial::mostrarDatosHistorial(){
    ui->tableWidget->setRowCount(0); // LIMPIAR CUALQUIER CONTENIDO PREVIO

    for(int i = 0; i < vectorHistorial.size(); ++i){
        Venta* venta = vectorHistorial[i];
        Pago* pago = vectorPago[i];

        if(venta && pago) {
            QString fecha = venta->getFecha();
            double monto = pago->getMonto();


            int row = ui->tableWidget->rowCount();

            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fecha));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(monto, 'f', 2)));
        }
    }

    ui->tableWidget->resizeColumnsToContents();

}



