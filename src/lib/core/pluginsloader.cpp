#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QMetaMethod>
#include <QPluginLoader>
#include <QSharedPointer>
#include <QSettings>
#include <QString>
#include "hevaa_consts.h"
#include "hidestring.h"
#include "customcomponent.h"
#include "imoduleplugin.h"
#include "pluginsloader.h"

using namespace  hevaa;

PluginsLoader::PluginsLoader(QObject *parent) : QObject(parent)
{

}

PluginsLoader::PluginsLoader(QString password, bool encode, QObject *parent) :
    QObject(parent),
    m_password(password), m_encode(encode)
{
    if (!encode && loadSettings())
    {
        loadModules();
        loadRobots();
        //connectModules(hevaa::MODULE_NAME_TELEGRAM, hevaa::MODULE_NAME_DATABASE);
        //connectModules(hevaa::MODULE_NAME_DATABASE, hevaa::MODULE_NAME_TELEGRAM);
        connectModules(hevaa::MODULE_NAME_TINKOFF, hevaa::MODULE_NAME_TELEGRAM);
        connectModules(hevaa::MODULE_NAME_TELEGRAM, hevaa::MODULE_NAME_TINKOFF);
        startModules();


//        auto root = hevaa::transport::Node::create(rootdata);
//        auto commands = hevaa::transport::Node::create(TINKOFF_SERVISES);
//        for (int i = 0; i < TINKOFF_SERVISES.count(); i++)
//        {
//            auto services = getServicesList(m_client, TINKOFF_SERVISES[i].toStringList()[0]);
//            if (services.count() > 0)
//            {
//                auto buttons = hevaa::transport::Node::create(services);
//                commands->appendChild(buttons);
//            }
//        }
//        root->appendChild(commands);



        hevaa::transport::message hm(hevaa::transport::Info, hevaa::transport::Node::create(hevaa::transport::Row{m_robots}));

        QMetaObject::invokeMethod(m_tgbot.data(), "init", Qt::DirectConnection,
                                  Q_ARG(hevaa::transport::message, hm));
    }
}

PluginsLoader::~PluginsLoader()
{
    stopModules();
    saveSettings(m_encode);
}

bool PluginsLoader::isSettingsOk()
{
    return !m_encode && m_isSettingsOk;
}

ModulesList *PluginsLoader::modules()
{
    return &m_modules;
}

hevaa::transport::Row *PluginsLoader::robots()
{
    return &m_robots;
}

bool PluginsLoader::loadSettings()
{
    QString SettingsFillPath = c_SettingsFile;
    QSettings settings(SettingsFillPath, QSettings::IniFormat);
    for(auto hs_key : m_app_settings.keys())
    {
        if (settings.value(hs_key).isNull())
        {
            m_isSettingsOk = false;
            qDebug() << "Parameter is not set" << hs_key;
        }
        hs_key.contains(alphaConst::qPrefix, Qt::CaseInsensitive) ? m_app_settings[hs_key] = codeDecode(settings.value(hs_key).toString(), m_password) : m_app_settings[hs_key] = settings.value(hs_key).toString();
    }
    return m_isSettingsOk;
}

void PluginsLoader::connectModules(const QString &sender, const QString &recipient)
{
    hevaa::IModulePlugin *senderModule = qobject_cast<hevaa::IModulePlugin *>(m_modules[sender]);
    hevaa::IModulePlugin *recipientModule = qobject_cast<hevaa::IModulePlugin *>(m_modules[recipient]);

    if ((senderModule) && (recipientModule)) {
        auto sender = senderModule->getComponent();
        auto reciever = recipientModule->getComponent();

        if ((sender) && (reciever)) {
            qDebug() << senderModule->moduleName() << "connected to" << recipientModule->moduleName();
            connect(sender.data(), &CustomComponent::transmitData, reciever.data(), &CustomComponent::handleData);
        } else {
            if (!reciever) qDebug() << "Recipient" << recipient << "does not exist";
            if (!sender) qDebug() << "Sender" << sender << " does not exist";
        }
    }
}

void PluginsLoader::startModules()
{
    foreach (QObject * value, m_modules) {
        auto module = qobject_cast<hevaa::IModulePlugin *>(value);
        if (module) {
            module->startModule();
        }
    }
}

void PluginsLoader::saveSettings(bool encode)
{
    QString fullFileName = c_SettingsFile;
    if (QFileInfo(fullFileName).exists())
    {
        QSettings settings(fullFileName, QSettings::IniFormat);
        if (!m_password.isEmpty() && encode)
        {
            qInfo() << "Settings file will be encoded...";
            QStringList childKeys = settings.childKeys();
            foreach (const QString &childKey, childKeys)
            {
                if (childKey.contains(alphaConst::qPrefix, Qt::CaseInsensitive))
                {
                    settings.setValue(childKey, codeDecode(settings.value(childKey).toString(), m_password));
                }
            }
        }
    } else {
        qInfo() << "File" << fullFileName << "not found. Creating a new settings file...";
        QSettings settings(fullFileName, QSettings::IniFormat);
        QMapIterator<QString, QString> it {m_app_settings};
        while(it.hasNext())
        {
            it.next();
            settings.setValue(it.key(), "");
        }
    }
}

void PluginsLoader::stopModules()
{
    foreach (QObject *value, m_modules) {
        auto module = qobject_cast<hevaa::IModulePlugin * >(value);
        if (module) {
            module->stopModule();
        }
    }
}

void PluginsLoader::loadModules()
{
    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath() + "/plugins");
    const auto entryList = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entryList) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        auto plugin = loader.instance();
        auto module = qobject_cast<hevaa::IModulePlugin *>(plugin);
        if (module) {
            qDebug() << "Plugin" << module->moduleName() << "is loaded";
            module->initModule(m_app_settings);
            if (QString::compare(module->moduleName(), COMPONENT_NAME_TELEGRAM, Qt::CaseInsensitive) == 0)
            {
                  m_tgbot = module->getComponent();
            }
            m_modules.insert(module->moduleName(), plugin);
        }
    }
}

void PluginsLoader::loadRobots()
{
    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath() + "/robots");
    const auto entryList = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entryList) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        auto plugin = loader.instance();
        auto module = qobject_cast<hevaa::IModulePlugin *>(plugin);
        if (module) {
            qDebug() << "Robot" << module->moduleName() << "is loaded";
            module->initModule(m_app_settings);
            m_robots.append(module->moduleName());
        }
    }
}
