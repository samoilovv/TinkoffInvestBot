#ifndef SIMPLEROBOTPLUGIN_H
#define SIMPLEROBOTPLUGIN_H

#include <QThread>
#include <QSharedPointer>
#include "robotinterface.h"
#include "customcomponent.h"
#include "investapiclient.h"

/*!
    \brief Простой торговый робот
*/
class SimpleRobot : public CustomComponent
{
    Q_OBJECT

public:
    SimpleRobot(AppSettins &plugin_settings);
    ~SimpleRobot();

protected:
    const hevaa::transport::Node ComponentInfo() final;
    QSharedPointer<InvestApiClient> m_client;

public slots:
    void handleData(const hevaa::transport::message &msg) final;

};

/*!
    \brief Менеджер простого торгового робота
*/
class SimpleRobotManager: public QObject, public hevaa::RobotInterface
{
    Q_OBJECT
    Q_CLASSINFO("name", "simplerobot")
    Q_CLASSINFO("caption", "Пример простого робота")
    Q_PLUGIN_METADATA(IID "ru.Hevaa.SimpleRobotPlugin.1.0" FILE "simpleRobotPlugin.json")
    Q_INTERFACES(
            hevaa::RobotInterface
            )

public:
    explicit SimpleRobotManager() = default;
    ~SimpleRobotManager();

    QString robotName() const override;
    QSharedPointer<CustomComponent> getComponent() const override;
    void init(AppSettins &plugin_settings) override;
    void start() override;
    void stop() override;

private:
    QThread m_thread;
    QSharedPointer<SimpleRobot> m_component;

};

#endif // SIMPLEROBOTPLUGIN_H
