#include "verhistorial.h"  // Incluir la definición de la clase verHistorial
#include "ui_verhistorial.h"  // Incluir la interfaz de usuario generada por Qt

verHistorial::verHistorial(std::vector<Pago* > &vectorPagoRef, std::vector<Venta *> &vectorHistorialRef, QWidget *parent)
    : QDialog(parent)  // Constructor de la clase verHistorial, hereda de QDialog
    , ui(new Ui::verHistorial)  // Inicializa la interfaz de usuario
    , vectorHistorial(vectorHistorialRef)  // Inicializa el vector de historial de ventas
    , vectorPago(vectorPagoRef)  // Inicializa el vector de pagos
{
    ui->setupUi(this);  // Configura la interfaz de usuario desde el archivo .ui

    // ESTABLECEMOS EL TITULO DE LA VENTANA
    this->setWindowTitle("Historial de ventas");  // Establece el título de la ventana

    // LLAMAMOS AL METODO PARA CARGAR LA HOJA DE ESTILOS
    initstylesheet();  // Llama a la función para aplicar un archivo de estilo a la ventana

    // CONFIGURAMOS LA TABLA VERCLIENTES PARA 2 COLUMNAS
    ui->tableWidget->setColumnCount(2);  // Establece 2 columnas en la tabla

    // DECLARAMOS QSTRINGLIST PARA LAS COLUMNAS
    QStringList encabezados;  // Declara una lista de cadenas para los encabezados

    encabezados << "Fecha" << "Monto";  // Asigna los encabezados de las columnas

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);  // Asigna los encabezados a la tabla
}

verHistorial::~verHistorial()  // Destructor de la clase verHistorial
{
    delete ui;  // Libera la memoria de la interfaz de usuario
}

void verHistorial::initstylesheet()  // Función para cargar y aplicar el estilo desde un archivo
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Abre el archivo de estilo
    bool styleOK = style.open(QFile::ReadOnly);  // Intenta abrir el archivo en modo solo lectura
    qDebug() << "Apertura de archivos: " << styleOK;  // Imprime si el archivo se ha abierto correctamente
    QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee el contenido del archivo y lo convierte en un QString
    this->setStyleSheet(stringEstilo);  // Aplica el estilo a la ventana
}

void verHistorial::mostrarDatosHistorial()  // Función para mostrar los datos del historial de ventas
{
    ui->tableWidget->setRowCount(0);  // Limpiar cualquier contenido previo de la tabla

    for (int i = 0; i < vectorHistorial.size(); ++i) {  // Recorre el vector de historial de ventas
        Venta* venta = vectorHistorial[i];  // Obtiene el objeto Venta en la posición i
        Pago* pago = vectorPago[i];  // Obtiene el objeto Pago en la posición i

        if (venta && pago) {  // Verifica que los objetos Venta y Pago no sean nulos
            QString fecha = venta->getFecha();  // Obtiene la fecha de la venta
            double monto = pago->getMonto();  // Obtiene el monto del pago

            int row = ui->tableWidget->rowCount();  // Obtiene el número de filas actuales en la tabla
            ui->tableWidget->insertRow(row);  // Inserta una nueva fila en la tabla

            // Inserta la fecha y el monto en las columnas correspondientes de la fila
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fecha));  // Inserta la fecha en la primera columna
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(monto, 'f', 2)));  // Inserta el monto en la segunda columna, con 2 decimales
        }
    }

    ui->tableWidget->resizeColumnsToContents();  // Ajusta automáticamente el tamaño de las columnas para que se adapten al contenido
}
