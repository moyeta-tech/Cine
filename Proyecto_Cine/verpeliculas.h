#ifndef VERPELICULAS_H
#define VERPELICULAS_H

#include <QDialog>
#include <QTableWidget>
#include <vector>
#include "peliculas.h"  // Incluye la clase Peliculas

namespace Ui {
class VerPeliculas;
}

class VerPeliculas : public QDialog
{
    Q_OBJECT

public:
    explicit VerPeliculas(std::vector<Peliculas*>& peliculas, QWidget *parent = nullptr);
    ~VerPeliculas();

private slots:
    // Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::VerPeliculas *ui;
    std::vector<Peliculas*>& peliculas;

public slots:
    // Declarar funciones
    void cargarPeliculasDesdeCSV(const QString &archivo);
    void agregarPeliculaATabla(const QString &titulo, int duracion, const QString &genero,
                               const QString &clasificacion, const QString &dias, const QString &horarios, const QString &sinopsis);
};

#endif // VERPELICULAS_H
