#ifndef VERPELICULAS_H // Verifica si el archivo no ha sido incluido previamente
#define VERPELICULAS_H // Define VERPELICULAS_H para evitar múltiples inclusiones del archivo


#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de diálogo

#include <QTableWidget> //Incluimos la biblioteca para trabajar con widgets de tabla en Qt
#include <vector> //Usamos std::vector para manejar colecciones dinámicas de objetos

#include "peliculas.h"  //Incluye la clase Peliculas para trabajar con los datos de las películas

namespace Ui {
class VerPeliculas;
}

class VerPeliculas : public QDialog
{
    Q_OBJECT

public:
    explicit VerPeliculas(std::vector<Peliculas*>& peliculas, QWidget *parent = nullptr); // Constructor que recibe un vector de películas
    ~VerPeliculas();

private slots:
    void initstylesheet(); //Slot para inicializar y cargar la hoja de estilo (CSS) para la ventana

private:
    Ui::VerPeliculas *ui; //Puntero a la interfaz gráfica generada automáticamente por Qt

    std::vector<Peliculas*>& peliculas; //Referencia al vector de películas para acceder a las películas almacenadas

public slots:
    void cargarPeliculasDesdeCSV(const QString &archivo); // Método para cargar las películas desde un archivo CSV
    void agregarPeliculaATabla(const QString &titulo, int duracion, const QString &genero, const QString &clasificacion, const QString &dias, const QString &horarios, const QString &sinopsis); //Método para agregar una película a la tabla
};

#endif // VERPELICULAS_H
