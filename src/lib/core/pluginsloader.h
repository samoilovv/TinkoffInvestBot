#ifndef PLUGINSLOADER_H
#define PLUGINSLOADER_H

#include <QObject>
#include "hevaa_common.h"
#include "hevaa_message.h"
#include "moduleinterface.h"

/*!
    \brief Загрузчик плагинов

    Находит совместимые плагины и роботы в специальных каталогах, загружает и запускает из работу.
    Также отвечает за чтение и сохранение настроек программы. Если в конструкторе класса передать
    пароль и включить флаг encode, то все пароли в файле настроек будут закодированы.
*/
class PluginsLoader : public QObject
{
    Q_OBJECT

public:
    explicit PluginsLoader(QObject *parent = nullptr);
    explicit PluginsLoader(QString password, bool encode = false, QObject *parent = nullptr);
    ~PluginsLoader();
    /// Проверка корректности файла настроек
    bool isSettingsOk();
    /// Список подключенных модулей программы
    ModulesList *modules();
    /// Список подключенных роботов
    hevaa::transport::Row *robots();

private:
    QString m_password;
    bool m_encode {false};
    AppSettins m_app_settings = {
        {"TGTOKEN", ""},
        {"DBHOST", ""},
        {"DBNAME", ""},
        {"DBUSER", ""},
        {"DBPASS", ""},
        {"TINKHOST", ""},
        {"TINKTOKEN", ""},
    };
    bool m_isSettingsOk {true};
    ModulesList m_modules;
    hevaa::transport::Row m_robots;
    QSharedPointer<CustomComponent> m_tgbot;
    QSharedPointer<CustomComponent> m_tinkoffInvest;
    bool loadSettings();
    void loadModules();
    void loadRobots();
    void connectModules(const QString &sender, const QString &recipient);
    void startModules();
    void stopModules();
    void saveSettings(bool encode = false);

signals:
    /// Отправить всю необходимую информацию для формирования главного меню
    void sendMainMenuInfo(const hevaa::transport::message &);

};

#endif // PLUGINSLOADER_H
