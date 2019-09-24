/** @file Main.cpp
 * Easily log several tasks elapsed time.
 * @author Adrien RICCIARDI
 */
#include <QApplication>
#include <MainWindow.hpp>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Display the application window
    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
