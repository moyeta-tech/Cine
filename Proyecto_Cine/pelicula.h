#ifndef PELICULA_H
#define PELICULA_H

#include <QMainWindow>

namespace Ui {
class Pelicula;
}

class Pelicula : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pelicula(QWidget *parent = nullptr);
    ~Pelicula();

private:
    Ui::Pelicula *ui;
};

#endif // PELICULA_H
