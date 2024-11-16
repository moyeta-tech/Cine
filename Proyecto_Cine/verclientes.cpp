#include "verclientes.h"
#include "ui_verclientes.h"

VerClientes::VerClientes(std::vector<Clientes *> &vectorClientesRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerClientes)
    , vectorClientes(vectorClientesRef)
{
    ui->setupUi(this);

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    //Conectamos los botones a los slots
    connect(ui->Boton_eliminar, &QPushButton::clicked, this, &VerClientes::eliminarCliente);
    connect(ui->Boton_cerrar, &QPushButton::clicked, this, &VerClientes::cerrarVentana);

    // CONFIGURAMOS LA TABLA VERCLIENTES PARA 6 COLUMNAS
    ui->tableWidget->setColumnCount(6);

    // DECLARAMOS QSTRINGLIST PARA LAS COLUMNAS
    QStringList encabezados;

    encabezados << "IDcliente" << "Nombre" << "Apellido" << "Dni" << "Edad" << "Telefono";

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);
}

VerClientes::~VerClientes()
{
    delete ui;
}

void VerClientes::actualizarTablaClientes(std::vector<Clientes *> &vectorClientes)
{

    ui->tableWidget->setRowCount(vectorClientes.size());

    for(int i = 0; i < vectorClientes.size(); i++)
    {
        Clientes *cliente = vectorClientes[i];

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(cliente->getIDcliente())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(cliente->getNombre())); // CONVERTIMOS A QSTRING
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(cliente->getApellido())); // CONVERTIMOS A QSTRING
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(cliente->getDni())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(cliente->getEdad())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(cliente->getTelefono())));
    }

}

void VerClientes::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

void VerClientes::cerrarVentana()
{
    accept();
}


void VerClientes::eliminarCliente()
{
    int FilaSeleccionada = ui->tableWidget->currentRow(); // OBTENEMOS EL NUMERO DE LAS FILA ACTUALES EN EL TABLEWIDGET

    if(FilaSeleccionada == -1) // SI NO HAY NINGUNA FILA SELECCIONADA Y SE APRETA EL BOTON DE ELIMINAR, SALE UN MENSAJE DE ERROR
    {
        QMessageBox::warning(this, "Advertencia", "Seleccione una fila por favor");
        return; // DETENEMOS LA EJECUCION DEL METODO SI NO SE SELECCIONA UNA FILA
    }
    bool borrar = true;
    if(borrar)
    {
        int res = QMessageBox::question(this, "Confirmar Selección", "¿Seguro quiere borrar esta fila?", QMessageBox::Yes | QMessageBox::Cancel);
        if(res == QMessageBox::Yes)
        {
            vectorClientes.erase(vectorClientes.begin() + FilaSeleccionada); // ELIMINAMOS DEL VECTOR Y DE LA TABLA
            ui->tableWidget->removeRow(FilaSeleccionada);
        }

    }
}

