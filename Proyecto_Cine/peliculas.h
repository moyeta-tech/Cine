#ifndef PELICULAS_H
#define PELICULAS_H

#include <QDialog>
#include <vector>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QTextStream>
#include <QList>

namespace Ui {
class Peliculas;
}

class Peliculas : public QDialog
{
    Q_OBJECT

public:
    explicit Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent = nullptr);
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

    QList<QTime> getHorarios() const;
    void setHorarios(const QList<QTime> &horarios);

    QDate getDia() const;
    void setDia(const QDate &fecha);

    void guardarPeliculasEnCSV(const QString &filename);
    void cargarPeliculasDesdeCSV(const QString &filename);

private slots:
   // void modificarPelicula();
    void eliminarPelicula();
    void buscarPelicula();
    void agregarPelicula();

    void initstylesheet();

signals:
    void peliAgregada(const QString &titulo, int duracion, const QString &genero,
                      const QString &clasificacion, const QString &sinopsis,
                      const QList<QTime> &horarios, const QDate &dia);

private:
    Ui::Peliculas *ui;
    QString Titulo;
    int Duracion;
    QString Genero;
    QString Clasificacion;
    QString Sinopsis;
    QList<QTime> horarios;
    QDate dia;
    std::vector<Peliculas*> &vectorPelicula;
    QString archivoCSV;  // Ruta del archivo CSV
};

#endif // PELICULAS_H
