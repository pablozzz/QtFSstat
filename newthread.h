//Special "wrappper" class for create object, which have to work in new thread & create new thread for it.

#ifndef NEWTHREAD_H
#define NEWTHREAD_H
#include <statistic.h>

class newThread : public QObject
{
    Q_OBJECT

private:

    QDir dir_path;
    int progress_value;

public:
    newThread(QDir dirPath);
    ~newThread();

    Statistic *stat;

private slots:
    void process();      //create statistic object and start calculate
    void progressDone(); //full progress bar;

signals:
    void done();
    void timerValue(int);
};

#endif // NEWTHREAD_H
