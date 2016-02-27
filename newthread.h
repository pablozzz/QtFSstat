#ifndef NEWTHREAD_H
#define NEWTHREAD_H
#include <statistic.h>
#include <qtimer.h>

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
    void process();
    void progressDone(); //full progress bar;

signals:
    void done();
    void timerValue(int);
};

#endif // NEWTHREAD_H
