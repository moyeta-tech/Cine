#ifndef HORARIOS_H
#define HORARIOS_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QListWidget>
#include "peliculas.h"

namespace Ui {
class Horarios;
}

class Horarios : public QDialog
{
    Q_OBJECT

public:
    explicit Horarios(std::vector<Peliculas*> &VectorPeliculasRef, QWidget *parent = nullptr);
    ~Horarios();

private slots:
    void mostrarHorariosYDia();

private:
    Ui::Horarios *ui;
    std::vector<Peliculas*> &VectorPeliculas;

    void initstylesheet();
};

#endif // HORARIOS_H
