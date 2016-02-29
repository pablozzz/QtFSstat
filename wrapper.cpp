#include "wrapper.h"


Wrapper::Wrapper(QDir dirPath)
{
    dir_path = dirPath;
    progress_value = 0;
    connect(this,SIGNAL(done()),this,SLOT(progressDone()));  //send 100% value in progress bar on main window
}
Wrapper::~Wrapper()
{

}

void Wrapper::process()
{
    progress_value = 0;
    emit timerValue(progress_value);   //clear progress bar
    statistic = new Statistic(dir_path);
    statistic->dirIterator();  //start statistic calculator
    emit done();
}

void Wrapper::progressDone()
{
    progress_value = 100;
    emit timerValue(progress_value);
}


