#include <QDebug>

#include "stopper.h"

using namespace std;

Stopper::Stopper(int _count): m_nValue(_count)
{
    m_ptimer = new QTimer(this);
    connect(m_ptimer, SIGNAL(timeout()), SLOT(setNextValue()));
}

void Stopper::slotDoWork()
{
    m_ptimer->start(100);
}

void Stopper::setNextValue()
{
    {
        if(m_nValue <= 0){
            m_ptimer->stop();
            emit finished();
            return;
        }
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

stopperManager::stopperManager(QObject *_owner, int _count)
{
    m_stopper = make_unique<Stopper>(_count);
    m_stopper->moveToThread(&m_thread);
    connect(&m_thread, SIGNAL(started()), m_stopper.get(), SLOT(slotDoWork()));
    connect(m_stopper.get(), SIGNAL(finished()), &m_thread, SLOT(quit()));
    connect(&m_stopper, SIGNAL(finished()), _owner, SLOT(quit()));
    qInfo() << "Application " << _owner->objectName() << "will be closed after" << _count << "seconds";
    m_thread.start();
}



