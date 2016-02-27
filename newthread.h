#ifndef NEWTHREAD_H
#define NEWTHREAD_H
#include <statistic.h>

class newThread : public QObject
{
    Q_OBJECT

private:

    Statistic *stat;
    QDir dir_path;

public:
    newThread(QDir dirPath);
    ~newThread();

    QString getPath();

    QMap<QString,qint64> sizeStore;     // file groups with sizes
    QMap<QString,qint64> countStore;    // file groups counter
    qint64 fileCounter;                 //all files in folder
    qint64 sizeCounter;                 //all files size
    QString subDirsCouter;               //subDirs

private slots:

    void process();

signals:
    void done();
};

#endif // NEWTHREAD_H
