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
                        //calculated statistic information in current folder
    void computeFdrStat(QDir currentDir);

    qint64 getFileCounter();       //return all files count
    qint64 getSizeCounter();       //reutrn size of all files
                      //return count of subdirectories only in selected folder
    QString getSubDirsCounter();
    QString getPath();                  //return selected folder path
                //Get absolute path and return filesize in bytes,kilobytes,etc.
    QString getFileSize(qint64 nSize);
    QMap<QString,qint64> getCountStore();
    QMap<QString,qint64> getSizeStore();



private:
    QMap<QString,qint64> countStore_;    // file groups counter
    QMap<QString,qint64> sizeStore_;     // file groups with sizes
    qint64 fileCounter_;                 //all files in folder
    qint64 sizeCounter_;                 //all files size
    qint64 subDirsCouter_;
    QDir dirPath_;
};

#endif // STATISTIC_H
