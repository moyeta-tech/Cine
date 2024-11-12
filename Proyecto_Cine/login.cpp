#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QRegularExpression>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowTitle("Iniciar sesion");
}

Login::~Login()
{
    delete ui;
}

// Acción cuando se hace clic en el botón "Iniciar sesión"
void LoginDialog::iniciarSesion()
{
    QString usuario = ui->usuarioLineEdit->text();
    QString contraseña = ui->contraseñaLineEdit->text();

    if (usuario.isEmpty() || contraseña.isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, ingresa un usuario y una contraseña.");
        return;
    }

    if (validarCredenciales(usuario, contraseña)) {
        // Si las credenciales son correctas, cerrar esta ventana e ir a la ventana principal
        accept();
    } else {
        QMessageBox::warning(this, "Credenciales Incorrectas", "El usuario o la contraseña son incorrectos.");
    }
}

// Acción cuando se hace clic en "Olvidé la contraseña"
void LoginDialog::olvideContraseña()
{
    QMessageBox::information(this, "Recuperar Contraseña", "Aquí puedes implementar la funcionalidad de recuperación de contraseña.");
}

// Acción cuando se hace clic en "Salir"
void LoginDialog::salirVentana()
{
    QApplication::quit();
}
