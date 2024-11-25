#include "iniciosesion.h"  // Incluir la clase de la ventana de inicio de sesión
#include <QApplication>     // Incluir la clase QApplication para gestionar la aplicación Qt

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // Crear la instancia de QApplication, necesaria para ejecutar cualquier aplicación Qt

    // Crear un objeto de la clase InicioSesion (ventana de inicio de sesión)
    InicioSesion loginDialog;

    // Ejecutar la ventana de inicio de sesión y esperar a que el usuario interactúe
    // Si el usuario cierra la ventana de inicio de sesión con éxito (aceptada), ejecutamos el ciclo de la aplicación
    if (loginDialog.exec() == QDialog::Accepted) {
        return a.exec();  // Ejecutamos la aplicación Qt
    }

    return 0;  // Si el usuario no acepta (cierra la ventana sin iniciar sesión), cerramos la aplicación
}
