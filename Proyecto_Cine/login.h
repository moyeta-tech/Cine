#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#include <QMessageBox>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void iniciarSesion();
    void olvideContraseña();
    void salirVentana();

private:
    Ui::Login *ui;

    bool validarCredenciales(const QString &usuario, const QString &contraseña);
};

#endif // LOGIN_H
