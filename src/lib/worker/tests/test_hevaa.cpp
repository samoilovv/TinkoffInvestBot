#include <QObject>
#include <QtTest>

#include "worker.h"

class HevaaTest : public QObject {
    Q_OBJECT

private Q_SLOTS:
    void sometest();

};

void HevaaTest::sometest()
{
    QThread * thread = new QThread;
    MyWorker * worker = new MyWorker();
    worker->moveToThread(thread);
    QSignalSpy spy(worker, SIGNAL(finished()));
    connect(thread, SIGNAL(started()), worker, SLOT(slotDoWork()));
    thread->start();
    QVERIFY(spy.wait());
}

QTEST_MAIN(HevaaTest)

#include "test_hevaa.moc"
