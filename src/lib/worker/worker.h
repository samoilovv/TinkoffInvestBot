#ifndef WORKER_H
#define WORKER_H

#include <QTimer>
#include <QThread>

#include "worker_export.h"

class WORKER_EXPORT MyWorker : public QObject {
Q_OBJECT
private:
    int     m_nValue;
    QTimer* m_ptimer;

public:
    MyWorker(int _count = 1);
    ~MyWorker()  = default;

signals:
    void valueChanged(int);
    void finished();

public slots:
    void slotDoWork();

private slots:
    void setNextValue();
};

class WORKER_EXPORT workerManager : public QObject {
    Q_OBJECT
public:
    workerManager(QObject * _owner = 0, int _count = 4);
    ~workerManager() = default;

private:
    QThread m_thread;
    std::unique_ptr<MyWorker> m_worker;

};

#endif // WORKER_H
