#ifndef PELICULAS_H
#define PELICULAS_H

#include <QDialog>
#include "vector"
#include <QFile>
#include "algorithm"
#include "QMessageBox"


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
    void initstylesheet();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
    void peliAgregada(QString titulo, int duracion, QString genero, QString clasificacion,
                      QString sinopsis);

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
