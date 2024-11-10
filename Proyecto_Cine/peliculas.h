#ifndef PELICULAS_H
#define PELICULAS_H

#include <QDialog>

namespace Ui {
class Peliculas;
}

class Peliculas : public QDialog
{
    Q_OBJECT

public:
    explicit Peliculas(QString titulo, int duracion, QString genero, QString clasificacion, QString sinopsis, QWidget *parent = nullptr);
    ~Peliculas();
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
    Ui::Peliculas *ui;
    QString Titulo;
    int Duracion;
    QString Genero;
    QString Clasificacion;
    QString Sinopsis;
};



#endif // PELICULAS_H
