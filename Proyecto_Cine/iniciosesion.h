#ifndef INICIOSESION_H
#define INICIOSESION_H

#include <QDialog>
#include <QFile>
#include "QDebug"

namespace Ui {
class InicioSesion;
}

class InicioSesion : public QDialog
{
    Q_OBJECT

public:
    explicit InicioSesion(QWidget *parent = nullptr);
    ~InicioSesion();

private slots:
    void iniciarSesion();
    void salirVentana();
    void recuperarPassword();
    void initstylesheet();

private:
    Ui::InicioSesion *ui;

    bool validarCredenciales(const QString &usuario, const QString &password);
};

#endif // INICIOSESION_H
