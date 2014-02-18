#include <QApplication>
#include "mainframe.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainFrame mainWindow;
    mainWindow.show();

    return app.exec();
}
