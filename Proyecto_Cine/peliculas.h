#ifndef PELICULAS_H
#define PELICULAS_H

#include <QWidget>

namespace Ui {
class peliculas;
}

class peliculas : public QWidget
{
    Q_OBJECT

public:
    explicit peliculas(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis, QWidget *parent = nullptr);
    ~peliculas();
    QString getTitulo();
    void setTitulo(QString titulo);
    int getDuracion();
    void setDuracion(int duracion);
    QString getGenero();
    void setGenero(QString genero);
    QString getClasificacion();
    void setClasificacion(QString clasificacion);
    QString getSinopsis();
    void setSinopsis(QString sinopsis);

private:
    Ui::peliculas *ui;
    QString Titulo;
    int Duracion;
    QString Genero;
    QString Clasificacion;
    QString Sinopsis;
};

#endif // PELICULAS_H
