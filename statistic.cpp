#include "statistic.h"

Statistic::Statistic(QDir dirpath)
{
    fileCounter = 0;
    sizeCounter = 0;
    subDirsCouter = 0;
    dir_path = dirpath;

}
qint64 Statistic::getfileCounter()
{
    return fileCounter;
}

qint64 Statistic::getsizeCounter()
{
    return sizeCounter;
}
QString Statistic::getsubdirsCounter()
{

    return QString::number(subDirsCouter);
}

QString Statistic::getPath()
{
    return dir_path.path();
}

void Statistic::dirIterator()
{
    this->getFolderStat(dir_path);      //get statistic information from cuttent folder
                                        //and start iterator
    QDir::Filters df = QDir::Dirs|QDir::NoDotAndDotDot; //filter for "." and ".." dirs
    QDirIterator it(dir_path.path(), df, QDirIterator::NoIteratorFlags);
    while (it.hasNext()) {
        {
            subDirsCouter++;
            this->getFolderStat(it.next());
        }
    }
}
void Statistic::getFolderStat(QDir current_path)
{
    qDebug() <<current_path;

    foreach (QString fileName,current_path.entryList(QDir::Files))
    {
        QString full_path = current_path.absoluteFilePath(fileName);
        QFileInfo *fileinfo= new QFileInfo(full_path);
        qint64 nSize = fileinfo->size();

        //add new extinsions and it's sizes in dictionary
        QString ext = fileinfo->completeSuffix();
        if (sizeStore.contains(ext))
        {
            sizeStore[ext] += nSize;
            countStore[ext]++;

        }
        else
        {
            sizeStore.insert(ext, nSize);
            countStore.insert(ext, 1);
        }
        sizeCounter += nSize;
        fileCounter++;
    }

}


QString Statistic::fileSize(qint64 nSize)
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
