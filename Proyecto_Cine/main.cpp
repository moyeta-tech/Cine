#include "pelicula.h"

#include <QApplication>

#include "iostream"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pelicula w;
    w.show();
    return a.exec();

}
