#include <QApplication>
#include "mainframe.h"
#include "intl.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	Fei::Intl *l = new Fei::Intl;
	l->installTranslators();

    MainFrame mainWindow;
    mainWindow.show();

    return app.exec();
}
