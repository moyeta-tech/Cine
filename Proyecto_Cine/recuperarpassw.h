#ifndef RECUPERARPASSW_H
#define RECUPERARPASSW_H

#include <QDialog>
#include <QFile>
#include <QDebug>

namespace Ui {
class RecuperarPassw;
}

class RecuperarPassw : public QDialog
{
    Q_OBJECT

public:
    explicit RecuperarPassw(QWidget *parent = nullptr);
    ~RecuperarPassw();

private slots:
    void recuperarPassword();
    void cancelarRecuperacion();

    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::RecuperarPassw *ui;
};

#endif // RECUPERARPASSW_H
