#ifndef SIMPLEROBOT2PLUGIN_H
#define SIMPLEROBOT2PLUGIN_H

#include <QThread>
#include <QSharedPointer>
#include "imoduleplugin.h"
#include "customcomponent.h"
#include "investapiclient.h"

/*!
    \brief Клиент сервисов Тинькофф Инвестиций
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
    void init(const hevaa::transport::message &msg) final;
    void handleData(const hevaa::transport::message &msg) final;

};

/*!
    \brief Менеджер Тинькофф Инвестиций

    Позволяет управлять счетами, открывать и закрывать позиции,
    запрашивать и анализировать различную торговую информацию и т.д.
*/
class SimpleRobot2Manager: public QObject, public hevaa::IModulePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.Hevaa.TinkoffInvestPlugin.1.0" FILE "tinkoffInvestPlugin.json")
    Q_INTERFACES(
            hevaa::IModulePlugin
            )

public:
    explicit SimpleRobot2Manager() = default;
    ~SimpleRobot2Manager();

    QString moduleName() const override;
    QSharedPointer<CustomComponent> getComponent() const override;
    void initModule(AppSettins &plugin_settings) override;
    void startModule() override;
    void stopModule() override;

private:
    QThread m_thread;
    QSharedPointer<SimpleRobot2Manager> m_component;
};

#endif // SIMPLEROBOT2PLUGIN_H
