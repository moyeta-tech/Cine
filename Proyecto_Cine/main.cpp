#include "cine.h"

#include <QApplication>

#include "iostream"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cine w;
    a.setWindowIcon(QIcon(":/images/src/icons/image cine.ico"));
    w.show();
    return a.exec();

}
