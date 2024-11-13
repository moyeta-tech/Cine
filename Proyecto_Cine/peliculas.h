#ifndef PELICULAS_H
#define PELICULAS_H

#include <QDialog>
<<<<<<< HEAD
#include "vector"
=======
#include <QFile>
>>>>>>> 724aafccd9b8b8dfb3091b12d66cdb715f57cf92

namespace Ui {
class Peliculas;
}

class Peliculas : public QDialog
{
    Q_OBJECT

public:
    explicit Peliculas(std::vector<Peliculas *> &vectorPeliculaRef, QWidget *parent = nullptr);
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

private slots:
<<<<<<< HEAD
    void on_pushButton_2_clicked();

signals:
    void peliAgregada(QString titulo, int duracion, QString genero, QString clasificacion,
                      QString sinopsis);
=======
    void initstylesheet();

>>>>>>> 724aafccd9b8b8dfb3091b12d66cdb715f57cf92
private:
    Ui::Peliculas *ui;
    QString Titulo;
    int Duracion;
    QString Genero;
    QString Clasificacion;
    QString Sinopsis;
    std::vector<Peliculas*> &vectorPelicula;
};



#endif // PELICULAS_H
