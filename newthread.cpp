#include "newthread.h"

newThread::newThread(QDir dirPath)
{
    dir_path = dirPath;
    fileCounter = 0;                // all files in folder
    sizeCounter = 0;                // all files size
}
newThread::~newThread()
{

}

void newThread::process()
{
    stat = new Statistic(dir_path);
    stat->dirIterator();

    sizeStore = stat->sizeStore;                         // file groups with sizes
    countStore = stat->countStore;                       // file groups counter

    fileCounter = stat->getfileCounter();                // all files in folder
    sizeCounter = stat->getsizeCounter();                // all files size
    subDirsCouter = stat->getsubdirsCounter();           // subdirecroties

    emit done();
}

QString newThread::getPath()
{
    return dir_path.path();
}
