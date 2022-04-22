#include <QDebug>

#include "worker.h"

using namespace std;

MyWorker::MyWorker(int _count): m_nValue(_count)
{
    m_ptimer = new QTimer(this);
    connect(m_ptimer, SIGNAL(timeout()), SLOT(setNextValue()));
}

void MyWorker::slotDoWork()
{
    m_ptimer->start(100);
}

void MyWorker::setNextValue()
{
    {
        if(m_nValue <= 0){
            m_ptimer->stop();
            emit finished();
            return;
        }
        //заполнить логгер
        emit valueChanged(--m_nValue);
        qInfo() << m_nValue;
    }
}

//for c++11 compatibility
#if __cplusplus < 201402L
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif

workerManager::workerManager(QObject * _owner, int _count)
{
    m_worker = make_unique<MyWorker>(_count);
    m_workerThread.setObjectName("WorkerThread");
    m_worker->moveToThread(&m_workerThread);
    connect(&m_workerThread, SIGNAL(started()), m_worker.get(), SLOT(slotDoWork()));
    connect(m_worker.get(), SIGNAL(finished()), &m_workerThread, SLOT(quit()));
    //выйти из программы после завершения потока workerThread
    connect(&m_workerThread, SIGNAL(finished()), _owner, SLOT(quit()));
    qInfo() << "Application " << _owner->objectName() << "will be closed after" << _count << "seconds";
    m_workerThread.start();
}



