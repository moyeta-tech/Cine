#include "recuperarpassw.h"
#include "ui_recuperarpassw.h"

#include <QMessageBox>
#include <QIcon>

RecuperarPassw::RecuperarPassw(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RecuperarPassw)
{
    ui->setupUi(this);

    //Establecemos el titulo de la ventana
    this->setWindowTitle("Recuperar contraseña");

    //Establecemos un icono a la ventana
    setWindowIcon(QIcon(":/images/src/icons/image cine.ico"));

    //Llamamos al slot para cargar el stylesheet
    initstylesheet();

    //Conectamos los botones a los slots
    connect(ui->Boton_rec, &QPushButton::clicked, this, &RecuperarPassw::recuperarPassword);
    connect(ui->Boton_cancelar, &QPushButton::clicked, this, &RecuperarPassw::cancelarRecuperacion);

    //Establecemos un icono a la recuperacion de contrañsea
    ui->label->setPixmap(QPixmap(":/images/src/icons/changepass.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

RecuperarPassw::~RecuperarPassw()
{
    delete ui;
}

void RecuperarPassw::recuperarPassword()
{
    QString email = ui->lineEdit_mail->text();

    if (email.isEmpty())
    {
        QMessageBox::warning(this, "Correo vacío", "Por favor, ingresa tu correo electrónico.");
        return;
    }

    // Simulamos que el correo "empleado@example.com" recupera la contraseña "1234"
    if (email == "empleado@example.com")
    {
        QMessageBox::information(this, "Recuperación exitosa", "Tu contraseña es: 1234");
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Correo no registrado", "El correo no está registrado.");
    }
}

void RecuperarPassw::cancelarRecuperacion()
{
    reject();
}

void RecuperarPassw::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-inicio.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}
