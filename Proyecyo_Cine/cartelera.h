#ifndef CARTELERA_H
#define CARTELERA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Cartelera;
}
QT_END_NAMESPACE

class Cartelera : public QMainWindow
{
    Q_OBJECT

public:
    Cartelera(QWidget *parent = nullptr);
    ~Cartelera();

private:
    Ui::Cartelera *ui;

    void cargarCartelera();

};
#endif // CARTELERA_H
