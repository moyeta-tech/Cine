#ifndef CINE_H
#define CINE_H

#include <QMainWindow>
#include "array"
#include "QDebug"

namespace Ui {
class Cine;
}

class Cine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cine(QWidget *parent = nullptr);
    ~Cine();

    // ATRIBUTOS
    QString Nombre;
    QString Ubicacion;
    std::array<int, 4> salas;
    // METODOS
    QString getNombre();
    void setNombre(QString nombre);
    QString getUbicacion();
    void setUbicacion(QString ubicacion);

private:
    Ui::Cine *ui;

};

#endif // CINE_H
