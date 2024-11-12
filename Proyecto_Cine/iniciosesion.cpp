#include "iniciosesion.h"
#include "ui_iniciosesion.h"

#include <QMessageBox>

InicioSesion::InicioSesion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InicioSesion)
{
    ui->setupUi(this);

    this->setWindowTitle("Iniciar sesion");
}

InicioSesion::~InicioSesion()
{
    delete ui;
}

bool InicioSesion::validarCredenciales(const QString &usuario, const QString &contraseña)
{
    // Aquí validamos con datos estáticos para el ejemplo.
    if (usuario == "empleado" && contraseña == "1234") {
        return true;
    }
    return false;
}

void InicioSesion::iniciarSesion()
{
    QString usuario = ui->lineEdit_id->text();
    QString contraseña = ui->lineEdit_contrasena->text();

    if (usuario.isEmpty() || contraseña.isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, ingresa un usuario y una contraseña.");
        return;
    }

    if (validarCredenciales(usuario, contraseña)) {
        // Si las credenciales son correctas, se acepta el login y se cierra la ventana de login
        accept();
    } else {
        QMessageBox::warning(this, "Credenciales Incorrectas", "El usuario o la contraseña son incorrectos.");
    }
}

void InicioSesion::salirVentana()
{
    // Si se hace clic en "Salir", cerramos la aplicación
    QApplication::quit();
}
