#ifndef PELICULAS_H
#define PELICULAS_H

#include <QDialog>

#include <vector>
#include <QFile>
#include <algorithm>
#include <QMessageBox>
#include <QDebug>


namespace Ui {
class Peliculas;
}

class Peliculas : public QDialog
{
    Q_OBJECT

public:
    explicit Peliculas(std::vector<Peliculas *> &vectorPeliculaRef, QWidget *parent = nullptr);
    ~Peliculas();

    QString getTitulo() const;
    void setTitulo(QString titulo);
    int getDuracion() const;
    void setDuracion(int duracion);
    QString getGenero() const;
    void setGenero(QString genero);
    QString getClasificacion() const;
    void setClasificacion(QString clasificacion);
    QString getSinopsis() const;
    void setSinopsis(QString sinopsis);

private slots:
    void agregarPelicula();
    void modificarPelicula();
    void eliminarPelicula();
    void guardarCambios();
    void buscarPelicula();

    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

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
