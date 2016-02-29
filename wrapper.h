//Special "wrappper" class for create object, which have to work in new thread & create new thread for it.

#ifndef WRAPPER_H
#define WRAPPER_H

#include <statistic.h>

class Wrapper : public QObject
{
    Q_OBJECT

public:
    Wrapper(QDir dirPath_);
    ~Wrapper();

    Statistic *statistic;

private:
    QDir dirPath_;
    int pBarValue_;

signals:
    void done();
    void timerValue(int);

private slots:
    void process();      //create statistic object and start calculate
    void progressDone(); //full progress bar;


};

#endif // WRAPPER_H
