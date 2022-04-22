#include <QSharedPointer>

#include "version.h"
#include "worker.h"
#include "LogConfigurator.h"
#include "simpleQtLogger.h"
#include "HevaaApplication.h"
#include "HevaaStandardPaths.h"

HevaaApplication::HevaaApplication(int& argc, char **argv[]) : QCoreApplication (argc, *argv)
{
    setOrganizationDomain("mamavrn.ru");
    setOrganizationName("mamavrn");
    setApplicationVersion(QString("%1").arg(MY_VERSION));
}

HevaaApplication::~HevaaApplication()
{
    QSettings settings(StandardPaths::hevaaStandardLocation(StandardPaths::ConfigHevaaLocation) + c_SettingsFile, QSettings::IniFormat);
    settings.setValue("count", 10);
}

void HevaaApplication::init()
{
    m_logConf = new LogConfigurator(this);
    auto header = QString("================ \r\n"
                      "\t Запуск приложения \r\n"
                      "============================================ \r\n");
    LS_INFO(header);

    this->setObjectName(applicationName());

    QSettings settings(StandardPaths::hevaaStandardLocation(StandardPaths::ConfigHevaaLocation) + c_SettingsFile, QSettings::IniFormat);
    int i = settings.value("count", 10).toUInt();
    WManager = QSharedPointer<workerManager>::create(this, i);
}


