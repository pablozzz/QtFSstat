#include "newthread.h"

newThread::newThread()
{

}

void newThread::run()
{
    for (int i=0; i<=100; ++i )
    {
        usleep(100000);
        emit progress(i);
    }
}
