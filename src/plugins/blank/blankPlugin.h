#ifndef BLANKPLUGIN_H
#define BLANKPLUGIN_H

#include <QThread>
#include "imoduleplugin.h"
#include "customcomponent.h"

class BlankComponent : public CustomComponent
{
Q_OBJECT

public:
    BlankComponent(AppSettins &plugin_settings);
    ~BlankComponent();

};

class BlankManager: public QObject, public hevaa::IModulePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.mamavrn.Hevaa.BlankPlugin.1.0" FILE "blankPlugin.json")
    Q_INTERFACES(
            hevaa::IModulePlugin
            )

public:
    explicit BlankManager() = default;
    ~BlankManager();

    QString moduleName() const override; // использовать objectName ?
    QSharedPointer<CustomComponent> getComponent() const override;
    void initModule(AppSettins &plugin_settings) override;
    void startModule() override;
    void stopModule() override;

private:
    QThread m_blankThread;
    QSharedPointer<BlankComponent> m_blankComponent;
};

#endif // BLANKPLUGIN_H
