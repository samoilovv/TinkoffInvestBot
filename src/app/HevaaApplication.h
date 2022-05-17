#ifndef MAIN_HEVAAAPPLICATION_H
#define MAIN_HEVAAAPPLICATION_H

#include <QCoreApplication>
#include <QSharedPointer>
#include "pluginsloader.h"
#include "worker.h"
#include "hevaa_common.h"

/*!
    \brief Телеграм-бот управления счетами в Тинькофф Инвестициях

    Для работы менеджеру требуются токен авторизации на торговой платформе Тинькофф Инвестиции
    и токен для доступа к телеграм-боту, которые указываются в файле настроек settings.ini.
    После первого запуска файл настроек будет зашифрован с помощью ключа, переданного в качестве первого аргумента.
*/
class HevaaApplication : public QCoreApplication
{
    Q_OBJECT

public:
    HevaaApplication(int& argc, char **argv[]);
    ~HevaaApplication() = default;
    void init(QString psw = "");

private:
    QString password;
    QSharedPointer<PluginsLoader> m_pluginsLoader;
    QSharedPointer<workerManager> WManager;
};

#endif // MAIN_HEVAAAPPLICATION_H

