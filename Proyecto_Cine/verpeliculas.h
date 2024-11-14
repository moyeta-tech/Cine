#ifndef VERPELICULAS_H
#define VERPELICULAS_H

#include <QDialog>
#include <QFile>

namespace Ui {
class VerPeliculas;
}

class VerPeliculas : public QDialog
{
    Q_OBJECT

public:
    explicit VerPeliculas(QWidget *parent = nullptr);
    ~VerPeliculas();

private slots:
    //Slot para inicializar y cargar la hoja de estilo (CSS) para el widget
    void initstylesheet();

private:
    Ui::VerPeliculas *ui;
};

#endif // VERPELICULAS_H
