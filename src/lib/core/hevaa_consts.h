#ifndef HEVAA_CONSTS_H
#define HEVAA_CONSTS_H

#include <QLatin1String>

namespace hevaa {

    static const QString APP_UNIQUE_SEMAPHORE = "Hevaa unique sync name";
    static const QString APP_UNIQUE_NAME = "Hevaa unique single apllication name";

    static const QString c_SettingsFile {"settings.ini"};

    static const QString MODULE_NAME_TELEGRAM      = QLatin1String("telegramBotModule");
    static const QString COMPONENT_NAME_TELEGRAM   = QLatin1String("telegramBotComponent");
    static const QString MODULE_NAME_DATABASE      = QLatin1String("dataBaseModule");
    static const QString COMPONENT_NAME_DATABASE   = QLatin1String("dataBaseComponent");
    static const QString MODULE_NAME_TINKOFF       = QLatin1String("tinkoffModule");
    static const QString COMPONENT_NAME_TINKOFF    = QLatin1String("tinkoffComponent");

}

#endif // HEVAA_CONSTS_H
