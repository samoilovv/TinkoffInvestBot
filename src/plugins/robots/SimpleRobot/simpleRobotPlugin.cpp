#include <QDebug>
#include <QCoreApplication>
#include <QMetaMethod>
#include "hevaa_consts.h"
#include "hevaa_transport.h"
#include "hevaa_tree.h"
#include "simpleRobotPlugin.h"
#include "customservice.h"
#include "sandboxservice.h"
#include "commontypes.h"

using namespace hevaa;

SimpleRobot::SimpleRobot(AppSettins &plugin_settings): CustomComponent(plugin_settings)
{
    setObjectName("MovingAverage");
    m_client = QSharedPointer<InvestApiClient>::create(m_plugin_settings["TINKHOST"].toStdString(), m_plugin_settings["TINKPASS"].toStdString());
}

SimpleRobot::~SimpleRobot()
{

}

const hevaa::transport::Node SimpleRobot::ComponentInfo()
{
    hevaa::transport::Row rootdata = {objectName()};
    auto root = hevaa::transport::Node::create(rootdata);
    return root;
}

void SimpleRobot::handleData(const hevaa::transport::message &msg)
{
    CustomComponent::handleData(msg);
    try {
        if (msg.type() == hevaa::transport::Command)
        {

        }
    } catch (std::exception& e) {
         qCritical() << QString("error: %1").arg(e.what());
    }
}

SimpleRobotManager::~SimpleRobotManager()
{

}

QString SimpleRobotManager::moduleName() const
{
    return "SimpleRobotModule";
}

QSharedPointer<CustomComponent> SimpleRobotManager::getComponent() const
{
    return m_component;
}

void SimpleRobotManager::initModule(AppSettins &plugin_settings)
{
    m_component = QSharedPointer<SimpleRobot>::create(plugin_settings);
}

void SimpleRobotManager::startModule()
{
    qDebug() << "The TinkoffManager thread is" << QThread::currentThread();

    m_thread.setObjectName(moduleName());
    m_component->moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, [](){ qDebug() << "tinkoffThread send signal started!"; });
    connect(&m_thread, &QThread::finished, m_component.data(), [](){ qDebug() << "tinkoffThread send signal finished!"; });

    qInfo() << "Starting" << m_thread.objectName() << "...";
    m_thread.start();
}

void SimpleRobotManager::stopModule()
{
    m_thread.requestInterruption();
    m_thread.quit();
    m_thread.wait();
}

