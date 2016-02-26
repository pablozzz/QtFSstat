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

    Statistic();
    QString fileSize(qint64 nSize);     //Get absolute path and return filesize in bytes,kilobytes,etc.
    void getFilesStat(QDir dir_path);   //Get full files statisic about folder dir_path
    void dirIterator(QDir dir_path);    //Subdirectories runner;
    void SubDirsCounter(QDir dir_path); //Count subdirectories in folder
    qint64 getfileCounter();
    qint64 getsizeCounter();
    QString getsubdirsCounter();
    QMap<QString,qint64> sizeStore;     // file groups with sizes
    QMap<QString,qint64> countStore;    // file groups counter

private:
    qint64 fileCounter;                 //all files in folder
    qint64 sizeCounter;                 //all files size
    qint64 subDirsCouter;
};

#endif // STATISTIC_H
