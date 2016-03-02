#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include <QSplashScreen>
#include <QTime>
#include "mainwindow.h"

class Pause : public QThread
{
public:
static void sleep(unsigned long secs) {
QThread::sleep(secs);
}
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //set font "Calibri" from recource file.
    QString fontPath = ":/fonts/Calibri.ttf"; //font file
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font("Calibri",11);
        a.setFont(font);
    }
    //add splash screen for slowly direcroties tree construction operation
    QPixmap pixmap(":/images/splash.png"); //splash image
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage(QObject::tr("Direcroties tree construction..."),
                    Qt::AlignLeft | Qt::AlignTop, Qt::white);

    MainWindow mainWindow;
    mainWindow.resize(900,500);
    mainWindow.moveToCenter();
    Pause::sleep(2);
    mainWindow.show();
    splash.finish(&mainWindow);
    splash.raise();

    return a.exec();
}

