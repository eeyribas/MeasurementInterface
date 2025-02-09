#ifndef LINECHARTTHREAD_H
#define LINECHARTTHREAD_H

#include <QThread>
#include <QMutex>

class LineChartThread : public QThread
{
    Q_OBJECT
public:
    explicit LineChartThread(QObject *parent = 0, bool b = false);
    void run();

    bool stop;

signals:
    void atLineChartValueChanged();
};

#endif // LINECHARTTHREAD_H
