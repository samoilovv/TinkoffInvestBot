#ifndef MAIN_HEVAAAPPLICATION_H
#define MAIN_HEVAAAPPLICATION_H

#include <QCoreApplication>
#include <QSharedPointer>
#include "pluginsloader.h"
#include "stopper.h"
#include "hevaa_common.h"

/*!
    \brief Телеграм-бот управления счетами в Тинькофф Инвестициях

    Для работы приложения требуются токен авторизации на торговой платформе Тинькофф Инвестиции
    и токен для доступа к телеграм-боту, которые указываются в файле настроек settings.ini.
    Пустой файл настроек settings.ini будет создан после первого запуска программы.
    При запуске с ключем -e (--encode) и паролем файл настроек будет зашифрован.
*/
class HevaaApplication : public QCoreApplication
{
    Q_OBJECT

public:
    HevaaApplication(int& argc, char **argv[]);
    ~HevaaApplication() = default;
    void init(QString psw = "", bool encode = false);

private:
    QString password;
    QSharedPointer<PluginsLoader> m_pluginsLoader;
    QSharedPointer<stopperManager> WManager;
};

#endif // MAIN_HEVAAAPPLICATION_H

