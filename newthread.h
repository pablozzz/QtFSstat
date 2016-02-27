#ifndef NEWTHREAD_H
#define NEWTHREAD_H
#include <statistic.h>

class newThread : public QObject
{
    Q_OBJECT

private:

    QDir dir_path;

public:
    newThread(QDir dirPath);
    ~newThread();

    Statistic *stat;

private slots:

    void process();

signals:
    void done();
};

#endif // NEWTHREAD_H
