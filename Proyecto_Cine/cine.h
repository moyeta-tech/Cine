#ifndef CINE_H
#define CINE_H

#include <QMainWindow>
#include "vector"

namespace Ui {
class Cine;
}

class Cine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cine(QWidget *parent = nullptr);
    Cine(QString nombre, QString ubicacion);
    ~Cine();
    QString getNombre;
    void setNombre(QString nombre);
    QString getUbicacion;
    void setUbicacion(QString ubicacion);
    std::vector<int> getSalas();
    void setSalas();


private:
    Ui::Cine *ui;
    QString Nombre;
    QString Ubicacion;
    std::vector<int> salas;
};

#endif // CINE_H
