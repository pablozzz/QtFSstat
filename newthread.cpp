#include "newthread.h"


newThread::newThread(QDir dirPath)
{
    dir_path = dirPath;
    progress_value = 0;
    connect(this,SIGNAL(done()),this,SLOT(progressDone()));
}
newThread::~newThread()
{

}

void newThread::process()
{
    progress_value = 0;
    emit timerValue(progress_value);   //clear progress bar
    stat = new Statistic(dir_path);
    stat->dirIterator();  //start statistic calculator
    emit done();
}

void newThread::progressDone()
{
    progress_value = 100;
    emit timerValue(progress_value);
}


