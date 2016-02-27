#include "newthread.h"

newThread::newThread(QDir dirPath)
{
    dir_path = dirPath;

}
newThread::~newThread()
{

}

void newThread::process()
{
    stat = new Statistic(dir_path);
    stat->dirIterator();

    emit done();
}
