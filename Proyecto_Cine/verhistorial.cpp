#include "verhistorial.h"
#include "ui_verhistorial.h"

verHistorial::verHistorial(std::vector<Pago* > &vectorPagoRef, std::vector<Venta *> &vectorHistorialRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::verHistorial)
    , vectorPago(vectorPagoRef)
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

    encabezados << "Fecha" << "Monto";

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);
    cargarDatosTabla();
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

void verHistorial::cargarDatosTabla(){
     ui->tableWidget->setRowCount(0);


    for(int i = 0; i < vectorHistorial.size(); i++){
        Venta *venta = vectorHistorial[i];
        Pago *pago = vectorPago[i];


        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(venta->getFecha()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(pago->getMonto(), 'f', 2)));
    }


}


void verHistorial::on_boton_cerrar_clicked()
{
    accept();
}


void verHistorial::on_boton_eliminar_clicked()
{
    int filaseleccionada = ui->tableWidget->currentRow();

    if(filaseleccionada == -1){
        QMessageBox::warning(this, "Advertencia", "Por favor, seleccione una fila");
        return;
    }
    bool borrar = true;
    if(borrar){
        int res = QMessageBox::question(this, "Confirmar Selección", "¿Seguro quiere borrar esta fila?", QMessageBox::Yes | QMessageBox::Cancel);
        if(res == QMessageBox::Yes){
            vectorHistorial.erase(vectorHistorial.begin() + filaseleccionada);
            vectorPago.erase(vectorPago.begin() + filaseleccionada);
            ui->tableWidget->removeRow(filaseleccionada);

        }
    }
}

