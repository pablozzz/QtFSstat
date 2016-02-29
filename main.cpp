#include <QApplication>
#include <QFont>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont newFont("Courier", 10, QFont::Bold, true); //set standart font for "clean" machine
    QApplication::setFont(newFont);

    MainWindow w;
    w.setMinimumSize(900,500);
    w.show();

    return a.exec();
}

