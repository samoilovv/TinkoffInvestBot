#ifndef TELEGRAMBOT_H
#define TELEGRAMBOT_H

#include <QThread>
#include <QSharedPointer>
#include "hevaa_common.h"
#include "hevaa_tree.h"
#include "moduleinterface.h"
#include "customcomponent.h"
#include <tgbot/tgbot.h>

using namespace TgBot;

/*!
    \brief Класс, поддерживающий соединение с сервером Телеграм-мессенджера

    Постоянное соединение с сервером Телеграма поддерживается при помощи "длинных опросов".
*/
class LongPollsExecuter: public QObject
{
Q_OBJECT

public:
    LongPollsExecuter(const QSharedPointer<TgBot::Bot> m_bot);

public slots:
    void execute();

private:
    QSharedPointer<TgBot::Bot> m_bot;

};

/*!
    \brief Телеграм бот, управляющий счетами и роботами
*/
class TelegramBot: public CustomComponent
{
Q_OBJECT

protected:
    void createMenu(hevaa::transport::Node menuInfo);
    InlineKeyboardMarkup::Ptr createButtons(hevaa::transport::Node buttonInfo);

private:
    QSharedPointer<TgBot::Bot> m_bot;
    QSharedPointer<LongPollsExecuter> m_longPollsExecutor;
    QThread m_longPollsThread;
    std::int64_t m_chatid {0};

public:
    TelegramBot(AppSettins plugin_settings);
    ~TelegramBot();

public slots:
    void init(const hevaa::transport::message &msg);
    void test();
    void handleData(const hevaa::transport::message &msg) final;
    void slotDoWork();

};

/*!
    \brief Менеджер телеграм бота
*/
class TelegramManager: public QObject, public hevaa::ModuleInterface
{
    Q_OBJECT
    Q_CLASSINFO("name", "TelegramBot")
    Q_PLUGIN_METADATA(IID "ru.Hevaa.TelegramPlugin.1.0" FILE "telegramPlugin.json")
    Q_INTERFACES(
            hevaa::ModuleInterface
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
