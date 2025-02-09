#include "processthread.h"

ProcessThread::ProcessThread(QObject *parent, bool b) :
    QThread(parent), stop(b)
{
}

void ProcessThread::run()
{
    for (;;) {
        QMutex mutex;
        mutex.lock();
        if (this->stop)
            break;
        mutex.unlock();

        emit atProcessValueChanged();
        this->msleep(500);
    }
}
