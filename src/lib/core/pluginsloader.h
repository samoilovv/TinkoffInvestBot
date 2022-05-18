#ifndef PLUGINSLOADER_H
#define PLUGINSLOADER_H

#include <QObject>

#include "hevaa_common.h"

class PluginsLoader : public QObject
{
    Q_OBJECT

public:
    explicit PluginsLoader(QObject *parent = nullptr);
    ~PluginsLoader();
    bool isSettingsOk();
    ModulesList *modulesList();

private:
    QString m_password;
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
    bool m_isSettingsOk {false};
    ModulesList m_modules_list;
    bool loadSettings();
    void loadModules();
    void connectModules(const QString &sender, const QString &recipient);
    void startModules();
    void stopModules();
    void saveSettings();
};

#endif // PLUGINSLOADER_H
