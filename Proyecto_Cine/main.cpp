#include "cine.h"

#include <QApplication>

#include "iniciosesion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Crear e iniciar el diálogo de inicio de sesión
    InicioSesion loginDialog;
    if (loginDialog.exec() == QDialog::Accepted)
    {
        //Si las credenciales son correctas, mostramos la ventana principal del cine
        Cine w;
        a.setWindowIcon(QIcon(":/images/src/icons/image cine.ico")); //Icono de la aplicación
        w.show();
        return a.exec();
    }

    //Si el inicio de sesión es cancelado o incorrecto, se termina la aplicación
    return 0;
}
