#ifndef PELICULAS_H // Verifica si PELICULAS_H no ha sido definido previamente
#define PELICULAS_H // Define PELICULAS_H para evitar múltiples inclusiones del archivo

#include <QDialog> //Incluimos la biblioteca QDialog para crear y manejar cuadros de dialogo

#include <vector> //Incluimos la biblioteca  estándar para manejo de vectores
#include <QFile> //Incluimos la biblioteca  para manejar operaciones de archivos
#include <QMessageBox> //Incluimos la biblioteca para mostrar mensajes emergentes al usuario
#include <QDebug> //Funcionalidad para imprimir mensajes de depuración
#include <QTime> //Incluimos la biblioteca  para manejar horarios
#include <QDate> //Incluimos la biblioteca  para manejar fechas
#include <QTextStream> //Incluimos la biblioteca  para manejar flujos de texto en archivos
#include <QList> //Incluimos la biblioteca  para listas dinámicas de elementos

namespace Ui {
class Peliculas;
}

class Peliculas : public QDialog
{
    Q_OBJECT

public:
    explicit Peliculas(std::vector<Peliculas*> &vectorPeliculaRef, QWidget *parent = nullptr); //Constructor para inicializar con referencia a un vector
    ~Peliculas();

    QString getTitulo() const; //Obtenemos el título de la película
    void setTitulo(QString titulo); //Establecemos el título de la película

    int getDuracion() const; //Obtenemos la duración de la película
    void setDuracion(int duracion); //Establecemos la duración de la película

    QString getGenero() const; //Obtenemos el género de la película
    void setGenero(QString genero); //Establecemos el género de la película

    QString getClasificacion() const; //Obtenemos la clasificación de la película
    void setClasificacion(QString clasificacion); //Establecemos la clasificación de la película

    QString getSinopsis() const; //Obtenemos la sinopsis de la película
    void setSinopsis(QString sinopsis); //Establecemos la sinopsis de la película

    QList<QTime> getHorarios() const; //Obtenemos la lista de horarios de la película
    void setHorarios(const QList<QTime> &horarios); //Establecemos la lista de horarios de la película

    QDate getDia() const; //Obtenemos el día de la película
    void setDia(const QDate &fecha); //Establecemos el día de la película

    void guardarPeliculasEnCSV(const QString &filename); //Metodo para guarda las películas en un archivo CSV
    void cargarPeliculasDesdeCSV(const QString &filename); //Metodo para carga las películas desde un archivo CSV


private slots:
    void eliminarPelicula(); //Slot para eliminar una película
    void buscarPelicula(); //Slot para buscar una película
    void agregarPelicula(); //Slot para agregar una película
    void initstylesheet(); //Slot para inicializar y aplicar la hoja de estilos (CSS)

signals:
    void peliAgregada(const QString &titulo, int duracion, const QString &genero, //Señal emitida cuando se agrega una película
                      const QString &clasificacion, const QString &sinopsis,
                      const QList<QTime> &horarios, const QDate &dia);

private:
    Ui::Peliculas *ui; //Puntero a la interfaz gráfica generada automáticamente
    QString Titulo; //Almacena el título de la película
    int Duracion; //Almacena la duración de la película en minutos
    QString Genero; //Almacena el género de la película
    QString Clasificacion; //Almacena la clasificación de la película (e.g., PG, R)
    QString Sinopsis; //Almacena la sinopsis de la película
    QList<QTime> horarios; //Lista de horarios en los que se proyectará la película
    QDate dia; //Fecha en la que se proyectará la película
    std::vector<Peliculas*> &vectorPelicula; //Referencia al vector global de películas
    QString archivoCSV; //Ruta del archivo CSV donde se guardarán los datos de películas
};

#endif // PELICULAS_H
