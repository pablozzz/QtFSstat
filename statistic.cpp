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

QMap<QString,qint64> Statistic::getCountStore()
{
    return countStore_;
}

QMap<QString,qint64> Statistic::getSizeStore()
{
    return sizeStore_;
}

void Statistic::startDirIterator()
{
    //count subdirs in current directory
    //add filter for exclude "." and ".." subdirectories
    foreach (QString DirName,dirPath_.entryList(QDir::Dirs|QDir::NoDotAndDotDot))
    {
        subDirsCouter_++;
    }

    //get statistic information from cuttent folder and start iterator
    this->computeFdrStat(dirPath_);
    QDir::Filters df = QDir::Dirs|QDir::NoDotAndDotDot|QDir::NoSymLinks;
    QDirIterator it(dirPath_.path(), df, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        {
            this->computeFdrStat(it.next());
        }
    }
}

void Statistic::computeFdrStat(QDir currentDiir)
{
    QDir::Filters ff = QDir::Files|QDir::Hidden|QDir::NoSymLinks;
    foreach (QFileInfo fileInfo,currentDiir.entryInfoList(ff))
    {
        qint64 nSize = fileInfo.size();
        sizeCounter_ += nSize;
        fileCounter_++;

        //add new extinsions and it's sizes in dictionary
        QString ext = fileInfo.completeSuffix();
        if (sizeStore_.contains(ext))
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
