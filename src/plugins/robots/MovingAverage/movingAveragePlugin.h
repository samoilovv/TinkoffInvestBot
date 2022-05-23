#ifndef MOVINGAVERAGEPLUGIN_H
#define MOVINGAVERAGEPLUGIN_H

#include <QThread>
#include <QSharedPointer>
#include "imoduleplugin.h"
#include "customcomponent.h"
#include "investapiclient.h"

class MovingAverage : public CustomComponent
{
Q_OBJECT

public:
    MovingAverage(AppSettins &plugin_settings);
    ~MovingAverage();

protected:
    const hevaa::transport::Node ComponentInfo() final;
    QSharedPointer<InvestApiClient> m_client;

public slots:
    void handleData(const hevaa::transport::message &msg) final;

};

class MovingAverageManager: public QObject, public hevaa::IModulePlugin
{
    Q_OBJECT
    Q_CLASSINFO("name", "movingaverage")
    Q_CLASSINFO("caption", "MovingAverage Robot")
    Q_PLUGIN_METADATA(IID "ru.Hevaa.MovingAveragePlugin.1.0" FILE "movingAveragePlugin.json")
    Q_INTERFACES(
            hevaa::IModulePlugin
            )

public:
    explicit MovingAverageManager() = default;
    ~MovingAverageManager();

    QString moduleName() const override;
    QSharedPointer<CustomComponent> getComponent() const override;
    void initModule(AppSettins &plugin_settings) override;
    void startModule() override;
    void stopModule() override;

private:
    QThread m_thread;
    QSharedPointer<MovingAverage> m_component;
};

#endif // MOVINGAVERAGEPLUGIN_H
