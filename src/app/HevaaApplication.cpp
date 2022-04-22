#include <csignal>
#include <QDebug>

#include "version.h"
#include "LogConfigurator.h"
#include "simpleQtLogger.h"
#include "HevaaApplication.h"

HevaaApplication::HevaaApplication(int& argc, char **argv[]) : QCoreApplication (argc, *argv)
{
    setOrganizationDomain("mamavrn.ru");
    setOrganizationName("mamavrn");
    setApplicationVersion(QString("%1").arg(MY_VERSION));
}

void HevaaApplication::init(QString psw)
{
    password = psw;
    m_logConf = QSharedPointer<LogConfigurator>::create(this);
    auto header = QString("================ \r\n"
                      "\t Запуск приложения \r\n"
                      "============================================ \r\n");
    LS_INFO(header);
    qDebug() << "The main thread is" << QThread::currentThread();
    this->setObjectName(applicationName());

    m_pluginsLoader = QSharedPointer<PluginsLoader>::create(password);
    if (m_pluginsLoader->isSettingsOk())
    {
        qDebug() << "Settings is Ok";

        signal(SIGINT, [](int s) {
            Q_UNUSED(s);
            qDebug() << "SIGINT got";
            qApp->quit();

        });
    } else {
        qDebug() << "Settings is not Ok. More details in log file.";
        WManager = QSharedPointer<workerManager>::create(this);
    }
}


