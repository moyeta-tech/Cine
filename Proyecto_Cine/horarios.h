#ifndef HORARIOS_H
#define HORARIOS_H

#include <QDialog>

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


private:
    Ui::Horarios *ui;

    QString Hora;
    QString Dia;
};

#endif // HORARIOS_H
