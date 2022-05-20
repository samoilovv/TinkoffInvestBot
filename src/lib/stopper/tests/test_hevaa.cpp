#include <QObject>
#include <QtTest>

#include "stopper.h"

class HevaaTest : public QObject {
    Q_OBJECT

private Q_SLOTS:
    void sometest();

};

void HevaaTest::sometest()
{
    QThread *thread = new QThread;
    Stopper *stopper = new Stopper();
    stopper->moveToThread(thread);
    QSignalSpy spy(stopper, SIGNAL(finished()));
    connect(thread, SIGNAL(started()), stopper, SLOT(slotDoWork()));
    thread->start();
    QVERIFY(spy.wait());
}

QTEST_MAIN(HevaaTest)

#include "test_hevaa.moc"
