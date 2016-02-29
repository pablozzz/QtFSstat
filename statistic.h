#ifndef STATISTIC_H
#define STATISTIC_H

#include <QDir>
#include <QDirIterator>
#include <QMap>
#include <QDebug>

class Statistic
{

public:
    Statistic(QDir dirPath);

    void startDirIterator();                 //Subdirectories runner;
    void computeFdrStat(QDir currentDir);  //calculated statistic information in current folder

    qint64 getFileCounter();            //return all files count
    qint64 getSizeCounter();            //reutrn size of all files
    QString getSubDirsCounter();        //return count of subdirectories only in selected folder
    QString getPath();                  //return selected folder path
    QString getFileSize(qint64 nSize);     //Get absolute path and return filesize in bytes,kilobytes,etc.

    QMap<QString,qint64> sizeStore_;     // file groups with sizes
    QMap<QString,qint64> countStore_;    // file groups counter


private:
    qint64 fileCounter_;                 //all files in folder
    qint64 sizeCounter_;                 //all files size
    qint64 subDirsCouter_;
    QDir dirPath_;
};

#endif // STATISTIC_H
