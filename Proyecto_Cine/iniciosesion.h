#ifndef INICIOSESION_H
#define INICIOSESION_H

#include <QDialog>
#include <QFile>
#include <QDebug>

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

    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::InicioSesion *ui;

    bool validarCredenciales(const QString &usuario, const QString &password);
};

#endif // INICIOSESION_H
