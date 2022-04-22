#ifndef HEVAA_CONSTS_H
#define HEVAA_CONSTS_H

#include <QLatin1String>

namespace hevaa {

    static const auto defCount = 6;
    static const auto c_SettingsFile {"/hevaa.ini"};
    static const auto c_investapi_prefix {"investapi_"};

    static const auto MODULE_NAME_BLANK         = QLatin1String("blankModule");
    static const auto COMPONENT_NAME_BLANK      = QLatin1String("blankComponent");
    static const auto MODULE_NAME_TELEGRAM      = QLatin1String("telegramBotModule");
    static const auto COMPONENT_NAME_TELEGRAM   = QLatin1String("telegramBotComponent");
    static const auto MODULE_NAME_DATABASE      = QLatin1String("dataBaseModule");
    static const auto COMPONENT_NAME_DATABASE   = QLatin1String("dataBaseComponent");
    static const auto MODULE_NAME_TINKOFF       = QLatin1String("tinkoffModule");
    static const auto COMPONENT_NAME_TINKOFF    = QLatin1String("tinkoffComponent");

}

#endif // HEVAA_CONSTS_H
