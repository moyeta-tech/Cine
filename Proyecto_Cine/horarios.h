#ifndef HORARIOS_H //Verifica si HORARIOS_H no ha sido definido previamente
#define HORARIOS_H //Define HORARIOS_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <QFile> //Incluimos la biblioteca para manejar archivos en Qt
#include <QMessageBox> //Incluimos la biblioteca  para mostrar cuadros de mensaje
#include <QListWidget> //Incluimos la biblioteca  para listas de elementos en la interfaz
#include "peliculas.h" //Incluimos la biblioteca  la definición de la clase `Peliculas`

namespace Ui {
class Horarios;
}

class Horarios : public QDialog
{
    Q_OBJECT

public:
    explicit Horarios(std::vector<Peliculas*> &VectorPeliculasRef, QWidget *parent = nullptr); // Constructor que recibe una referencia al vector de películas y un widget padre opcional
    ~Horarios();

private slots:
    void mostrarHorariosYDia(); //Slot para mostrar horarios y días asociados a las películas

private:
    Ui::Horarios *ui; //Puntero a la interfaz gráfica generada automáticamente

    std::vector<Peliculas*> &VectorPeliculas; //Referencia al vector que almacena las películas

    void initstylesheet(); //Metodo para inicializar y aplicar una hoja de estilo (CSS)
};

#endif // HORARIOS_H
