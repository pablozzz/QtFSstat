#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumSize(900,500);
    w.show();

    return a.exec();
}
//#include "main.moc"
