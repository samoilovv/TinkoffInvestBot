#include <QDebug>
#include <QStringList>
#include <QCoreApplication>
#include "telegramBotPlugin.h"
#include "hevaa_message.h"
#include "hevaa_consts.h"

void TelegramBot::createMenu(hevaa::transport::Node menuInfo)
{
    //команды и обработка команд
    std::vector<BotCommand::Ptr> commands;
    auto currentnode = menuInfo.get();
    for (int i = 0; i < currentnode->childCount(); i++)
    {
        auto currentchild = currentnode->child(i);
        for (int command_index = 0; command_index < currentchild->columnCount(); command_index++)
        {
            if (currentchild->data(command_index).toStringList().count() > 1)
            {
                BotCommand::Ptr cmdArray(new BotCommand);
                auto vCommand = currentchild->data(command_index).toStringList().at(0).toStdString();
                auto vDescription = currentchild->data(command_index).toStringList().at(1).toStdString();
                cmdArray->command = vCommand;
                cmdArray->description = vDescription;
                commands.push_back(cmdArray);
                auto buttons = currentchild->child(command_index);
                if (buttons)
                {
                    auto keyboard = createButtoms(buttons);
                    m_bot->getEvents().onCommand(vCommand, [this, keyboard, vDescription](Message::Ptr message) {
                        m_chatid = message->chat->id;
                        qDebug() << "Chat id:" << m_chatid;
                        m_bot->getApi().sendMessage(m_chatid, vDescription, false, 0, keyboard, "MarkdownV2");
                    });
                }
            }
        }
    }

    m_bot->getApi().setMyCommands(commands);
}

InlineKeyboardMarkup::Ptr TelegramBot::createButtoms(hevaa::transport::Node buttomInfo)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    std::vector<InlineKeyboardButton::Ptr> row;
    for (int button_index = 0; button_index < buttomInfo->columnCount(); button_index++)
    {
        InlineKeyboardButton::Ptr SandBoxButton(new InlineKeyboardButton);
        auto vButtonText = buttomInfo->data(button_index).toStringList()[0];
        auto vSrv = buttomInfo->data(button_index).toStringList()[1];
        auto vCallbackData = vSrv + vButtonText;
        SandBoxButton->text = vButtonText.toStdString();
        SandBoxButton->callbackData = vCallbackData.toStdString();
        row.push_back(SandBoxButton);
        if (button_index % 2 || button_index == buttomInfo->columnCount() - 1)
        {
            keyboard->inlineKeyboard.push_back(row);
            row.clear();
        }
        m_bot->getEvents().onCallbackQuery([this, vButtonText, vCallbackData, vSrv](CallbackQuery::Ptr query) {
            if (StringTools::startsWith(query->data, vCallbackData.toStdString())) {
                hevaa::transport::message msg(hevaa::transport::Command, hevaa::transport::Node::create(hevaa::transport::Row{vButtonText, vSrv}));
                emit transmitData(msg);
            }
        });
    }
    return keyboard;
}

TelegramBot::TelegramBot(AppSettins plugin_settings): CustomComponent(plugin_settings)
{
    setObjectName(hevaa::COMPONENT_NAME_TELEGRAM);

    std::string token;
    token.append(m_plugin_settings["TOKEN"].toStdString());
    token.append(":");
    token.append(m_plugin_settings["TGPASS"].toStdString());
    m_bot = QSharedPointer<Bot>::create(token);
    m_longPollsExecutor = QSharedPointer<LongPollsExecuter>::create(m_bot);
    m_longPollsExecutor->moveToThread(&m_longPollsThread);
    connect(&m_longPollsThread, &QThread::started, m_longPollsExecutor.get(), &LongPollsExecuter::execute, Qt::QueuedConnection);
    connect(&m_longPollsThread, &QThread::started, [](){ qDebug() << "longPollsThread send signal started!"; });
    m_longPollsThread.start();
    qDebug() << objectName() << "created and timer started!";
}

TelegramBot::~TelegramBot()
{
    m_longPollsThread.requestInterruption();
    m_longPollsThread.quit();
    m_longPollsThread.wait();
}

void TelegramBot::handleData(const hevaa::transport::message &msg)
{
    CustomComponent::handleData(msg);
    if (msg.type() == hevaa::transport::HandshakeAnswer)
    {
        createMenu(msg.body());
    }
    if (msg.body() && m_chatid) {
        m_bot->getApi().sendMessage(m_chatid, msg.body()->data(0).toString().toStdString());
   }
}

void TelegramBot::slotDoWork()
{
    qDebug() << "The TelegramBot thread is" << QThread::currentThread();


    m_bot->getEvents().onCommand("start", [this](Message::Ptr message) {
        m_chatid = message->chat->id;
        qDebug() << "Chat id:" << m_chatid;
        m_bot->getApi().sendMessage(m_chatid, "TinkoffInvestBot is started");
    });

    //передавать сообщения в бд
    m_bot->getEvents().onAnyMessage([this/*, &keyboard*/](Message::Ptr message) {

        qInfo() << QString("User %2 wrote %1").arg(message->text.c_str()).arg(message->from->firstName.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        m_chatid = message->chat->id;
        qDebug() << "Chat id:" << m_chatid;

    //            auto keyboard = createButtoms(nullptr);
    //            m_bot->getApi().sendMessage(m_chatid, "Your message is: " + message->text, false,  0, keyboard, "MarkdownV2");

        //запись в БД
        QStringList sl;
        sl << QString::fromStdString(message->from->username) << QString::fromStdString(message->text);
        hevaa::transport::message hm(hevaa::transport::Info, hevaa::transport::Node::create(hevaa::transport::Row({sl})));
        emit transmitData(hm);
    });

    qInfo() << QString("Bot username: %1").arg(m_bot->getApi().getMe()->username.c_str());
}

TelegramManager::~TelegramManager()
{

}

QString TelegramManager::moduleName() const
{
    return hevaa::MODULE_NAME_TELEGRAM;
}

QSharedPointer<CustomComponent> TelegramManager::getComponent() const
{
    return m_telegramBot;
}

void TelegramManager::initModule(AppSettins &plugin_settings)
{
    m_telegramBot = QSharedPointer<TelegramBot>::create(plugin_settings);
}

void TelegramManager::startModule()
{
    qDebug() << "The TelegramManager thread is" << QThread::currentThread();

    m_telegramThread.setObjectName(moduleName());
    m_telegramBot->moveToThread(&m_telegramThread);

    connect(&m_telegramThread, &QThread::started, [](){ qDebug() << "telegramThread send signal started!"; });
    connect(&m_telegramThread, &QThread::finished, m_telegramBot.data(), [](){ qDebug() << "telegramThread send signal finished!"; });

    connect(&m_telegramThread, &QThread::started, m_telegramBot.data(), &TelegramBot::slotDoWork, Qt::QueuedConnection);

    qInfo() << "Starting" << m_telegramThread.objectName() << "...";
    m_telegramThread.start();
}

void TelegramManager::stopModule()
{
    m_telegramThread.requestInterruption();
    m_telegramThread.quit();
    m_telegramThread.wait();
}

LongPollsExecuter::LongPollsExecuter(const QSharedPointer<Bot> m_bot) : m_bot(m_bot)
{

}

void LongPollsExecuter::execute()
{
    try {
        m_bot->getApi().deleteWebhook();
        TgLongPoll longPoll(*m_bot.data());
        while (true) {
            if (QThread::currentThread()->isInterruptionRequested()) {
                return;
            }
            qInfo() << "Long poll started";
            longPoll.start();
            QCoreApplication::processEvents();
        }
    } catch (TgBot::TgException& e) {
         qCritical() << QString("error: %1").arg(e.what());
    }
}
