#include "verempleados.h"
#include "ui_verempleados.h"
#include "QDir"

VerEmpleados::VerEmpleados(std::vector<Empleados *> &vectorEmpleadosRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerEmpleados)
    , vectorEmpleados(vectorEmpleadosRef)
{
    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Tabla de empleados");

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    //Conectamos los botones a los slots
    connect(ui->Boton_eliminar, &QPushButton::clicked, this, &::VerEmpleados::eliminarEmpleado);
    connect(ui->Boton_cerrar, &QPushButton::clicked, this, &VerEmpleados::cerrarVentana);

    // CONFIGURAMOS LA TABLA VERCLIENTES PARA 6 COLUMNAS
      ui->tableWidget->setColumnCount(6);

    // DECLARAMOS QSTRINGLIST PARA LAS COLUMNAS

    QStringList encabezados;

    encabezados << "IDempleado" << "Nombre" << "Apellido" << "Dni" << "Edad" << "Telefono";

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);
}

VerEmpleados::~VerEmpleados()
{

    delete ui;
}

void VerEmpleados::actualizarTablaEmpleados(std::vector<Empleados *> &vectorEmpleados)
{
    ui->tableWidget->setRowCount(vectorEmpleados.size());

    for(int i = 0; i < vectorEmpleados.size(); i++)
    {
        if(vectorEmpleados[i] == nullptr){
            qDebug() << "Empleado nulo en el vector";
            continue;
        }
        Empleados *empleado = vectorEmpleados[i];

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(empleado->getIDempleado())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(empleado->getNombre()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(empleado->getApellido()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(empleado->getDni())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(empleado->getEdad())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(empleado->getTelefono())));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(empleado->getPuesto()));


    }
}

void VerEmpleados::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}



void VerEmpleados::cerrarVentana()
{
    accept(); // METODO CREADO POR SI EL USUARIO PRESIONA CERRAR, SE CIERRA
}


void VerEmpleados::eliminarEmpleado()
{
    int FilaSeleccionada = ui->tableWidget->currentRow(); // OBTENEMOS LA FILA

    qDebug() << "Fila seleccionada: " << FilaSeleccionada;
    qDebug() << "Tamano del vector empleados: " << vectorEmpleados.size();

    if(FilaSeleccionada == -1)
    {
        QMessageBox::warning(this, "Advertencia", "Por favor, seleccione una fila");
        return; // SE DETIENE LA EJECUCION DEL METODO SI NO SE SELECCIONA UNA FILA
    }

    if(FilaSeleccionada < 0 || FilaSeleccionada >= vectorEmpleados.size()){
        QMessageBox::critical(this, "Error", "El indice seleccionado no es valido");
        return;
    }

    int res = QMessageBox::question(this, "Confirmar selección", "¿Seguro quiere borrar esta fila?", QMessageBox::Yes | QMessageBox::Cancel);

    if(res == QMessageBox::Yes){
        vectorEmpleados.erase(vectorEmpleados.begin() + FilaSeleccionada);

        ui->tableWidget->removeRow(FilaSeleccionada);
        QMessageBox::information(this, "Aviso", "Fila Eliminada correctamente");
    }
}
/*
void VerEmpleados::escribirArchivo(QString Archivo, int id, QString nombre, QString apellido, int dni, int edad, int telefono, QString puesto){
    QString linea = QString::number(id) + ',' + nombre + ',' + apellido + ',' + QString::number(dni) + ',' + QString::number(edad) + ',' + QString::number(telefono) + ',' + puesto + '\n';
    qDebug() << "Linea" << linea;

    QFile file(Archivo);
    if(file.open(QIODevice::Append | QIODevice::Text)){
        QTextStream out(&file);
        out << linea;
        file.close();
        qDebug() << "Archivo escrito correctamente: ";
    } else {
        qDebug() << "Error al abrir el archivo: ";
    }

    actualizarTablaEmpleados(vectorEmpleados);
}
*/

/*
void VerEmpleados::leerArchivo(QString Archivo){
  //  Archivo = QDir::currentPath() + "/empleados.csv";

    QFile file(Archivo);
    QString Contenido;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        Contenido = file.readAll();
        file.close();
        lineasLeidas = Contenido.split('\n', Qt::SkipEmptyParts);

        QSet<QString> lineasUnicas;
                                        // ESTO SE REALIZA PARA QUE SE AGREGUEN SOLO FILAS UNICAS A LA TABLA

        for (const QString& linea : lineasLeidas) {
            lineasUnicas.insert(linea); // Solo agrega líneas únicas
        }

        lineasLeidas = QStringList(lineasUnicas.begin(), lineasUnicas.end());
        qDebug() << "lineas leidas: " << lineasLeidas;

        vectorEmpleados.clear();

        for(const QString& linea : lineasLeidas){
            QStringList campos = linea.split(',');
            if(campos.size() == 7){
                Empleados *empleado = new Empleados(
                    vectorEmpleados,
                    campos[0].toInt(),
                    campos[1],
                    campos[2],
                    campos[3].toInt(),
                    campos[4].toInt(),
                    campos[5].toInt(),
                    campos[6]

                );
                vectorEmpleados.push_back(empleado);
                escribirArchivo("empleados.csv",
                                empleado->getIDempleado(),
                                empleado->getNombre(),
                                empleado->getApellido(),
                                empleado->getDni(),
                                empleado->getEdad(),
                                empleado->getTelefono(),
                                empleado->getPuesto()
                                );
            }
        }
         escribirTabla();
    } else {
        qDebug() << "no se pudo abrir el archivo";
    }
}
*/
/*
void VerEmpleados::escribirTabla(){
    int row = 0;
    QStringList campos;

    ui->tableWidget->setRowCount(0);
    for(QString &linea : lineasLeidas){
        campos = linea.split(',');
        if(campos.size() == 7){
            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(campos[0]));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(campos[1]));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(campos[2]));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(campos[3]));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(campos[4]));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(campos[5]));
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(campos[6]));
            row++;
        }
    }
}
*/
