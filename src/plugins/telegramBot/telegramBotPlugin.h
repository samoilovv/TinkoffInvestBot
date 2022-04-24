#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H

#include <QThread>
#include <QSharedPointer>

#include "hevaa_common.h"
#include "hevaa_tree.h"
#include "imoduleplugin.h"
#include "customcomponent.h"
#include <tgbot/tgbot.h>

using namespace TgBot;

class TelegramBot: public CustomComponent
{
Q_OBJECT

protected:
    void createMenu(hevaa::transport::Node menuInfo);
    InlineKeyboardMarkup::Ptr createButtoms(hevaa::transport::Node buttomInfo);

private:
    QSharedPointer<TgBot::Bot> m_bot;
    std::int64_t m_chatid {0};

public:
    TelegramBot(AppSettins plugin_settings);
    ~TelegramBot();

public slots:
    void handleData(const hevaa::transport::message &msg) final;
    void slotDoWork();

};

class TelegramManager: public QObject, public hevaa::IModulePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.Hevaa.TelegramPlugin.1.0" FILE "telegramPlugin.json")
    Q_INTERFACES(
            hevaa::IModulePlugin
            )

public:
    explicit TelegramManager() = default;
    ~TelegramManager();

    QString moduleName() const override;
    QSharedPointer<CustomComponent> getComponent() const override;
    void initModule(AppSettins &plugin_settings) override;
    void startModule() override;
    void stopModule() override;

private:
    QThread m_telegramThread;
    QSharedPointer<TelegramBot> m_telegramBot;

};

#endif // TELEGRAMBOT_H
