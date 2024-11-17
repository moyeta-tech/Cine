#ifndef PELICULAS_H
#define PELICULAS_H

#include <QDialog>
#include <vector>
#include <QFile>
#include <algorithm>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QTextStream>

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

    QTime getHorario() const;
    void setHorario(const QTime &hora);

    QDate getDia() const;
    void setDia(const QDate &fecha);

    void guardarCambios(const QString &archivo);
    static std::vector<Peliculas*> cargarPeliculas(const QString &archivo);

private slots:
    void agregarPelicula();
    void modificarPelicula();
    void eliminarPelicula();
    void buscarPelicula();

    void initstylesheet();

signals:
    void peliAgregada(QString titulo, int duracion, QString genero, QString clasificacion,
                      QString sinopsis, QTime horario, QDate dia);

private:
    Ui::Peliculas *ui;
    QString Titulo;
    int Duracion;
    QString Genero;
    QString Clasificacion;
    QString Sinopsis;
    QTime horario;
    QDate dia;
    std::vector<Peliculas*> &vectorPelicula;
};

#endif // PELICULAS_H
