#include <QApplication>
#include <QFont>
#include <QFontDatabase>
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

    MainWindow w;
    w.setMinimumSize(900,500);
    w.show();

    return a.exec();
}

