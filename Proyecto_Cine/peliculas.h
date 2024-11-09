#ifndef PELICULAS_H
#define PELICULAS_H

#include <QWidget>

namespace Ui {
class peliculas;
}

class peliculas : public QWidget
{
    Q_OBJECT

public:
    explicit peliculas(QWidget *parent = nullptr);
    ~peliculas();

private:
    Ui::peliculas *ui;
};

#endif // PELICULAS_H
