#include "iniciosesion.h"  // Incluir la clase de la ventana de inicio de sesión
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Crear la ventana de inicio de sesión
    InicioSesion loginDialog;

    // Mostrar la ventana de inicio de sesión
    if (loginDialog.exec() == QDialog::Accepted) {
        // Si el inicio de sesión es exitoso, ejecuta el resto de la aplicación o muestra la siguiente ventana
        // Por ejemplo, puedes iniciar una ventana principal aquí:
        // MainWindow w;
        // w.show();

        // Si no quieres mostrar otra ventana, simplemente finalizas la aplicación
        return a.exec();
    }

    // Si el inicio de sesión falla o se cancela, se termina la aplicación
    return 0;
}
