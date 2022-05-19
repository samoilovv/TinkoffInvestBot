#ifndef PLUGINSLOADER_H
#define PLUGINSLOADER_H

#include <QObject>

#include "hevaa_common.h"

class PluginsLoader : public QObject
{
    Q_OBJECT

public:
    explicit PluginsLoader(QObject *parent = nullptr);
    explicit PluginsLoader(QString password, bool encode = false, QObject *parent = nullptr);
    ~PluginsLoader();
    bool isSettingsOk();
    ModulesList *modules();

private:
    QString m_password;
    bool m_encode {false};
    AppSettins m_app_settings = {
        {"TOKEN", ""},
        {"TGPASS", ""},
        {"DBHOST", ""},
        {"DBNAME", ""},
        {"DBUSER", ""},
        {"DBPASS", ""},
        {"TINKHOST", ""},
        {"TINKPASS", ""},
    };
    bool m_isSettingsOk {true};
    ModulesList m_modules;
    QStringList m_modulesList;
    bool loadSettings();
    void loadModules();
    void loadRobots();
    void connectModules(const QString &sender, const QString &recipient);
    void startModules();
    void stopModules();
    void saveSettings(bool encode = false);
};

#endif // PLUGINSLOADER_H
