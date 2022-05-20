#ifndef STOPPER_H
#define STOPPER_H

#include <QTimer>
#include <QThread>

class Stopper : public QObject {

    Q_OBJECT
private:
    int m_nValue;
    QTimer *m_ptimer;

public:
    Stopper(int _count = 1);
    ~Stopper()  = default;

signals:
    void valueChanged(int);
    void finished();

public slots:
    void slotDoWork();

private slots:
    void setNextValue();
};

/*!
    \brief Класс, необходимый для корректного завершения работы программы

    Остановка всех запущенных потоков приложения и сохранения состояния и результатов работы.
*/
class stopperManager : public QObject {

    Q_OBJECT

public:
    stopperManager(QObject * _owner = 0, int _count = 4);
    ~stopperManager() = default;

private:
    QThread m_thread;
    std::unique_ptr<Stopper> m_stopper;

};

#endif // STOPPER_H
