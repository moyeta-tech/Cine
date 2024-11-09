#ifndef HORARIOS_H
#define HORARIOS_H

#include "peliculas.h"
#include <QWidget>

namespace Ui {
class Horarios;
}

class Horarios : public QWidget
{
    Q_OBJECT

public:
    explicit Horarios(QString hora, QString dia, peliculas *pelicula, QWidget *parent = nullptr);
    ~Horarios();
    QString getHora();
    void setHora(QString hora);
    QString getDia();
    void setDia(QString dia);
    void getPelicula();
    void setPelicula(peliculas *pelicula);



private:
    Ui::Horarios *ui;
    QString Hora;
    QString Dia;
    peliculas *Pelicula;
};

#endif // HORARIOS_H
