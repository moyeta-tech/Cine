#include "iniciosesion.h"
#include "recuperarpassw.h"
#include "ui_iniciosesion.h"

#include <QMessageBox>
#include <QIcon>

InicioSesion::InicioSesion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InicioSesion)
{
    ui->setupUi(this);

    this->setWindowTitle("Iniciar sesion");
    setWindowIcon(QIcon(":/images/src/icons/image cine.ico"));
    initstylesheet();

    connect(ui->Boton_iniciar, &QPushButton::clicked, this, &InicioSesion::iniciarSesion);
    connect(ui->Boton_salir, &QPushButton::clicked, this, &InicioSesion::salirVentana);
    connect(ui->Boton_olvide, &QPushButton::clicked, this, &InicioSesion::recuperarPassword);

    ui->label->setPixmap(QPixmap(":/images/src/icons/login.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

InicioSesion::~InicioSesion()
{
    delete ui;
}

bool InicioSesion::validarCredenciales(const QString &usuario, const QString &password)
{
    // Aquí validamos con datos estáticos para el ejemplo.
    if (usuario == "empleado" && password == "1234")
    {
        return true;
    }
    return false;
}

void InicioSesion::iniciarSesion()
{
    QString usuario = ui->lineEdit_id->text();
    QString password = ui->lineEdit_contrasena->text();

    if (usuario.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, ingresa un usuario y una contraseña.");
        return;
    }

    if (validarCredenciales(usuario, password))
    {
        // Si las credenciales son correctas, se acepta el login y se cierra la ventana de login
        accept();
    }
    else
    {
        ui->label->setPixmap(QPixmap(":/images/src/icons/wrongpass.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QMessageBox::warning(this, "Credenciales Incorrectas", "El usuario o la contraseña son incorrectos.");
    }
}

void InicioSesion::salirVentana()
{
    this->close();  // Cierra solo la ventana actual (InicioSesion)
}


void InicioSesion::recuperarPassword()
{
    // Abrimos la ventana de recuperación de contraseña
    RecuperarPassw recupDialog;
    recupDialog.exec();
}

void InicioSesion::initstylesheet()
{
    QFile style(":/src/stylesheet/stylesheet-inicio.css");
    bool styleOK = style.open(QFile::ReadOnly);
    qDebug() << "Apertura de archivos: " <<styleOK;
    QString stringEstilo = QString::fromLatin1(style.readAll());
    this->setStyleSheet(stringEstilo);
}

