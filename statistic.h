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
    void dirIterator();                 //Subdirectories runner;
    void fileFinder(QDir current_dir);  //calculated statistic information in current folder
    qint64 getfileCounter();            //return all files count
    qint64 getsizeCounter();            //reutrn size of all files
    QString getsubdirsCounter();        //return count of subdirectories only in selected folder
    QString getPath();                  //return selected folder path

    QMap<QString,qint64> sizeStore;     // file groups with sizes
    QMap<QString,qint64> countStore;    // file groups counter


private:

    qint64 fileCounter;                 //all files in folder
    qint64 sizeCounter;                 //all files size
    qint64 subDirsCouter;
    QDir dir_path;
};

#endif // STATISTIC_H
