#include "statistic.h"

Statistic::Statistic(QDir dirPath)
{
    fileCounter_ = 0;
    sizeCounter_ = 0;
    subDirsCouter_ = 0;
    dirPath_ = dirPath;

}
qint64 Statistic::getFileCounter()
{
    return fileCounter_;
}

qint64 Statistic::getSizeCounter()
{
    return sizeCounter_;
}
QString Statistic::getSubDirsCounter()
{

    return QString::number(subDirsCouter_);
}

QString Statistic::getPath()
{
    return dirPath_.path();
}


void Statistic::dirIterator()
{
    //count subdirs in current directory
    foreach (QString DirName,dirPath_.entryList(QDir::Dirs|QDir::NoDotAndDotDot)) //For exclude "." and ".." subdirectories
    {
        subDirsCouter_++;
    }

    //get statistic information from cuttent folder and start iterator
    this->fileFinder(dirPath_);
    QDir::Filters df = QDir::Dirs|QDir::NoDotAndDotDot|QDir::NoSymLinks; //filter for "." and ".." dirs
    QDirIterator it(dirPath_.path(), df, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        {
            this->fileFinder(it.next());
        }
    }
}

void Statistic::fileFinder(QDir currentDiir)
{
    foreach (QFileInfo fileInfo,currentDiir.entryInfoList(QDir::Files|QDir::Hidden|QDir::NoSymLinks))
    {
        qint64 nSize = fileInfo.size();
        sizeCounter_ += nSize;
        fileCounter_++;

        //add new extinsions and it's sizes in dictionary
        QString ext = fileInfo.completeSuffix();
        if (sizeStore_.contains(ext))             //Only one Qmap obj slowly search
        {
            sizeStore_[ext] += nSize;
            countStore_[ext]++;

        }
        else
        {
            sizeStore_.insert(ext, nSize);
            countStore_.insert(ext, 1);
        }
    }
}


QString Statistic::getFileSize(qint64 nSize)
{
    int i = 0;
    for (;nSize > 1023; nSize/=1024, i++)
    {
        if(i >= 4)
        {
            break;
        }

    }
    return QString().setNum(nSize)+"BKMGT"[i];

}
