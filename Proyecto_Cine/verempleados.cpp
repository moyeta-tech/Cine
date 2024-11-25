#include "verempleados.h"  // Incluir la definición de la clase VerEmpleados
#include "ui_verempleados.h"  // Incluir la interfaz de usuario generada por Qt
#include "empleados.h"  // Incluir la clase Empleados
#include <QDir>  // Incluir QDir para manejar rutas de archivos y directorios
#include <QDebug>  // Incluir QDebug para imprimir mensajes de depuración
#include <QFile>  // Incluir QFile para manejar archivos
#include <QTextStream>  // Incluir QTextStream para leer el contenido del archivo como texto

VerEmpleados::VerEmpleados(std::vector<Empleados*>& empleados, QWidget *parent) :
    QDialog(parent),  // Constructor de la clase VerEmpleados, hereda de QDialog
    ui(new Ui::VerEmpleados),  // Inicializa la interfaz de usuario
    empleados(empleados)  // Inicializa el vector de empleados
{
    ui->setupUi(this);  // Configura la interfaz de usuario desde el archivo .ui

    this->setWindowTitle("Listado de empleados"); //Establecemos el nombre ed la ventana

    // Llamamos al slot para cargar el stylesheet
    initstylesheet();  // Aplica un archivo de estilo a la ventana

    // Configurar el QTableWidget
    ui->tableWidget->setColumnCount(7);  // Establece 7 columnas en la tabla
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nombre", "Apellido", "DNI", "Edad", "Teléfono", "Puesto"});  // Asigna las etiquetas a las columnas de la tabla

    // Ruta del archivo CSV desde el directorio de ejecución
    QString rutaArchivo = QDir::currentPath() + "/empleados.csv";  // Define la ruta del archivo CSV
    qDebug() << "Ruta para cargar archivo: " << rutaArchivo;  // Imprime la ruta del archivo CSV en la consola

    // Cargar empleados desde el archivo CSV
    cargarEmpleadosDesdeCSV(rutaArchivo);  // Llama a la función para cargar los empleados desde el archivo CSV
}

VerEmpleados::~VerEmpleados()  // Destructor de la clase VerEmpleados
{
    delete ui;  // Libera la memoria de la interfaz de usuario
}

void VerEmpleados::initstylesheet()  // Función para cargar y aplicar el estilo desde un archivo
{
    QFile style(":/src/stylesheet/stylesheet-ventanas.css");  // Abre el archivo de estilo
    if (style.open(QFile::ReadOnly)) {  // Si el archivo se abre correctamente
        QString stringEstilo = QString::fromLatin1(style.readAll());  // Lee todo el contenido del archivo
        this->setStyleSheet(stringEstilo);  // Aplica el estilo a la ventana
    } else {
        qDebug() << "No se pudo cargar el archivo de estilo.";  // Imprime un mensaje si no se puede cargar el archivo de estilo
    }
}

void VerEmpleados::cargarEmpleadosDesdeCSV(const QString &archivo)  // Función para cargar los empleados desde un archivo CSV
{
    QFile file(archivo);  // Crea un objeto QFile para abrir el archivo CSV
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // Abre el archivo en modo solo lectura
        qDebug() << "No se pudo abrir el archivo CSV para lectura.";  // Imprime un mensaje si no se puede abrir el archivo
        return;  // Sale de la función si el archivo no se puede abrir
    }

    QTextStream stream(&file);  // Crea un flujo de texto para leer el archivo
    QString line;  // Variable para almacenar cada línea del archivo
    while (!stream.atEnd()) {  // Mientras no se llegue al final del archivo
        line = stream.readLine();  // Lee una línea del archivo
        QStringList campos = line.split(',');  // Divide la línea en partes usando la coma como delimitador

        // Verificar que la línea tenga el número correcto de campos
        if (campos.size() == 7) {  // Aseguramos que hay 7 campos (ID, Nombre, Apellido, DNI, Edad, Teléfono, Puesto)
            int id = campos[0].toInt();  // Convierte el primer campo a entero (ID)
            QString nombre = campos[1];  // El segundo campo es el nombre
            QString apellido = campos[2];  // El tercer campo es el apellido
            int dni = campos[3].toInt();  // El cuarto campo es el DNI
            int edad = campos[4].toInt();  // El quinto campo es la edad
            int telefono = campos[5].toInt();  // El sexto campo es el teléfono
            QString puesto = campos[6];  // El séptimo campo es el puesto del empleado

            // Agregar empleado a la tabla
            agregarEmpleadoATabla(id, nombre, apellido, dni, edad, telefono, puesto);  // Llama a la función para agregar el empleado a la tabla
        } else {
            qDebug() << "Línea inválida en el archivo: " << line;  // Imprime un mensaje si la línea no tiene el número correcto de campos
        }
    }

    file.close();  // Cierra el archivo después de leerlo
}

void VerEmpleados::agregarEmpleadoATabla(int id, const QString &nombre, const QString &apellido, int dni, int edad, int telefono, const QString &puesto)  // Función para agregar un empleado a la tabla
{
    int row = ui->tableWidget->rowCount();  // Obtiene el número de filas actuales en la tabla
    ui->tableWidget->insertRow(row);  // Inserta una nueva fila en la tabla

    // Inserta los datos del empleado en las celdas correspondientes
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));  // Inserta el ID del empleado en la primera columna
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nombre));  // Inserta el nombre del empleado en la segunda columna
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(apellido));  // Inserta el apellido del empleado en la tercera columna
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(dni)));  // Inserta el DNI del empleado en la cuarta columna
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(edad)));  // Inserta la edad del empleado en la quinta columna
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(telefono)));  // Inserta el teléfono del empleado en la sexta columna
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(puesto));  // Inserta el puesto del empleado en la séptima columna
}
