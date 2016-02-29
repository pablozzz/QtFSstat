#include "wrapper.h"


Wrapper::Wrapper(QDir dirPath)
{
    dirPath_ = dirPath;
    pBarValue_ = 0;
    connect(this,SIGNAL(done()),this,SLOT(progressDone()));  //send 100% value in progress bar on main window
}
Wrapper::~Wrapper()
{

}

void Wrapper::process()
{
    pBarValue_ = 0;
    emit timerValue(pBarValue_);   //clear progress bar
    statistic = new Statistic(dirPath_);
    statistic->startDirIterator();  //start statistic calculator
    emit done();
}

void Wrapper::progressDone()
{
    pBarValue_ = 100;
    emit timerValue(pBarValue_);
}

