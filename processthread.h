#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>
#include <QMutex>

class ProcessThread : public QThread
{
    Q_OBJECT
public:
    explicit ProcessThread(QObject *parent = 0, bool b = false);
    void run();

    bool stop;

signals:
    void atProcessValueChanged();
};

#endif // PROCESSTHREAD_H
