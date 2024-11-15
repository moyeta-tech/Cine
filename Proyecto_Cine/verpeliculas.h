#ifndef VERPELICULAS_H
#define VERPELICULAS_H

#include <QDialog>
#include <QFile>
#include "peliculas.h"

namespace Ui {
class VerPeliculas;
}

class VerPeliculas : public QDialog
{
    Q_OBJECT

public:
    explicit VerPeliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent = nullptr);
    ~VerPeliculas();

    // METODO PARA AGREGAR LAS PELICULAS A LA TABLA

    void actualizaPeliculasTabla(std::vector<Peliculas *> &vectorPelicula);

private slots:
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

    void on_Boton_cerrar_clicked();

private:
    Ui::VerPeliculas *ui;
    std::vector<Peliculas*> &vectorPelicula;
};

#endif // VERPELICULAS_H
