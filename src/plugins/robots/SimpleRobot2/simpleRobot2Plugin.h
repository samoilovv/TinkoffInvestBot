#ifndef SIMPLEROBOT2PLUGIN_H
#define SIMPLEROBOT2PLUGIN_H

#include <QThread>
#include <QSharedPointer>
#include "robotinterface.h"
#include "customcomponent.h"
#include "investapiclient.h"

/*!
    \brief Пример простого робота
*/
class SimpleRobot2Component : public CustomComponent
{
Q_OBJECT

public:
    SimpleRobot2Component(AppSettins &plugin_settings);
    ~SimpleRobot2Component();

protected:
    const hevaa::transport::Node ComponentInfo() final;
    QSharedPointer<InvestApiClient> m_client;

public slots:
    void handleData(const hevaa::transport::message &msg) final;

};

/*!
    \brief Менеджер простого робота
*/
class SimpleRobot2Manager: public QObject, public hevaa::RobotInterface
{
    Q_OBJECT
    Q_CLASSINFO("name", "simplerobot2")
    Q_CLASSINFO("caption", "Еще один простой робот")
    Q_PLUGIN_METADATA(IID "ru.Hevaa.SimpleRobot2Plugin.1.0" FILE "simpleRobot2Plugin.json")
    Q_INTERFACES(
            hevaa::ModuleInterface
            )

public:
    explicit SimpleRobot2Manager() = default;
    ~SimpleRobot2Manager();

    QString robotName() const override;
    QSharedPointer<CustomComponent> getComponent() const override;
    void init(AppSettins &plugin_settings) override;
    void start() override;
    void stop() override;

private:
    QThread m_thread;
    QSharedPointer<CustomComponent> m_component;
};

#endif // SIMPLEROBOT2PLUGIN_H
