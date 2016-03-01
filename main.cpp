#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include "startwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //set font "Calibri" from recource file.

    QString fontPath = ":/fonts/Calibri.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font("Calibri",11);
        a.setFont(font);
    }

    StartWindow* startWindow = new StartWindow;

    startWindow->show();
    startWindow->setMinimumSize(300,100);

    MainWindow mainWindow;
    mainWindow.setMinimumSize(900,500);

    delete(startWindow);
    mainWindow.show();


    return a.exec();
}

