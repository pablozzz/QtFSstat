#ifndef STATISTIC_H
#define STATISTIC_H

#include <QDir>
#include <QDirIterator>
#include <QMap>
#include <QDebug>

class Statistic
{

private slots:

public:

    Statistic(QDir dirpath);
    QString fileSize(qint64 nSize);     //Get absolute path and return filesize in bytes,kilobytes,etc.
    void dirIterator();    //Subdirectories runner;
    void getFolderStat(QDir current_path); //calculated statistic information in current folder
    qint64 getfileCounter();
    qint64 getsizeCounter();
    QString getsubdirsCounter();
    QMap<QString,qint64> sizeStore;     // file groups with sizes
    QMap<QString,qint64> countStore;    // file groups counter
    QString getPath();

private:

    qint64 fileCounter;                 //all files in folder
    qint64 sizeCounter;                 //all files size
    qint64 subDirsCouter;
    QDir dir_path;
};

#endif // STATISTIC_H
