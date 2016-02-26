#include "statistic.h"

Statistic::Statistic()
{
    fileCounter = 0;
    sizeCounter = 0;
}
qint64 Statistic::getfileCounter()
{
    return fileCounter;
}

qint64 Statistic::getsizeCounter()
{
    return fileCounter;
}

void Statistic::dirIterator(QDir dir_path)
{
    //Files counter
    QDirIterator it(dir_path, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        this->getFilesStat(it.next());
    }

    //print all extensions size
    QMap<QString,qint64> ::iterator iter = sizeStore.begin();
    for (;iter != sizeStore.end(); ++iter)
    {
        qDebug() << "Filgroup: " <<iter.key() << "Size: " <<this->fileSize(iter.value());

    }
    //print all extensions count
    QMap<QString,qint64> ::iterator iter2 = countStore.begin();
    for (;iter2 != countStore.end(); ++iter2)
    {
        qDebug() << "Filgroup: " <<iter2.key() << "Count: " << iter2.value();

    }

}
void Statistic::getFilesStat(QDir dir_path)
{

    foreach (QString fileName,dir_path.entryList(QDir::Files))
    {
        QString full_path = dir_path.absoluteFilePath(fileName);
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
void Statistic::SubDirsCounter(QDir dir_path)
{
    //Subdirectories counter
    int subdir_counter = 0;
    foreach (QString DirName,dir_path.entryList(QDir::Dirs))
    {
        subdir_counter++;
    }
    subdir_counter -=2; //For exclude "." and ".." subdirectories
    qDebug() << "Subdirectories: " << subdir_counter;
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
