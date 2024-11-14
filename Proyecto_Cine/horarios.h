#ifndef HORARIOS_H
#define HORARIOS_H

#include <QDialog>
#include <QFile>

namespace Ui {
class Horarios;
}

class Horarios : public QDialog
{
    Q_OBJECT

public:
    explicit Horarios(QString hora, QString dia, QWidget *parent = nullptr);
    ~Horarios();

    QString getHora();
    void setHora(QString hora);
    QString getDia();
    void setDia(QString dia);

private slots:
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::Horarios *ui;

    QString Hora;
    QString Dia;
};

#endif // HORARIOS_H
