#include "linechartthread.h"

LineChartThread::LineChartThread(QObject *parent, bool b) :
    QThread(parent), stop(b)
{
}

void LineChartThread::run()
{
    for (;;) {
        QMutex mutex;
        mutex.lock();
        if (this->stop)
            break;
        mutex.unlock();

        emit atLineChartValueChanged();
        this->msleep(500);
    }
}
