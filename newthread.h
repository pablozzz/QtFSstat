#ifndef NEWTHREAD_H
#define NEWTHREAD_H
#include <QThread>

class newThread : public QThread
{
    Q_OBJECT

public:
    newThread();
    void run();

signals:
    void progress(int);
};

#endif // NEWTHREAD_H
