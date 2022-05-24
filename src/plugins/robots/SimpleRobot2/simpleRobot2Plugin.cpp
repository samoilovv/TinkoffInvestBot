#include <QDebug>
#include <QCoreApplication>
#include <QMetaMethod>
#include "hevaa_consts.h"
#include "hevaa_transport.h"
#include "hevaa_tree.h"
#include "simpleRobot2Plugin.h"
#include "customservice.h"
#include "sandboxservice.h"
#include "commontypes.h"

using namespace hevaa;

SimpleRobot2Component::SimpleRobot2Component(AppSettins &plugin_settings): CustomComponent(plugin_settings)
{
    setObjectName("Robot2");
    m_client = QSharedPointer<InvestApiClient>::create(m_plugin_settings["TINKHOST"].toStdString(), m_plugin_settings["TINKTOKEN"].toStdString());
}

SimpleRobot2Component::~SimpleRobot2Component()
{

}

const hevaa::transport::Node SimpleRobot2Component::ComponentInfo()
{
    hevaa::transport::Row rootdata = {objectName()};
    auto root = hevaa::transport::Node::create(rootdata);
    return root;
}

void SimpleRobot2Component::handleData(const hevaa::transport::message &msg)
{
    CustomComponent::handleData(msg);
    try {
        if (msg.type() == hevaa::transport::Command)
        {
            qDebug() << "Sending request to tinkoff...";

            ServiceReply reply;
            QString func = msg.body()->data(0).toString();
            QString srv = msg.body()->data(1).toString();
            if (m_client->service(srv.toStdString()).get())
            {
                //todo
            } else
            {
                qDebug() << "There is no such service:" << srv;
            }
        }
    } catch (std::exception& e) {
         qCritical() << QString("error: %1").arg(e.what());
    }
}

SimpleRobot2Manager::~SimpleRobot2Manager()
{

}

QString SimpleRobot2Manager::robotName() const
{
    return "Robot2";
}

QSharedPointer<CustomComponent> SimpleRobot2Manager::getComponent() const
{
    return m_component;
}

void SimpleRobot2Manager::init(AppSettins &plugin_settings)
{
    m_component = QSharedPointer<SimpleRobot2Component>::create(plugin_settings);
}

void SimpleRobot2Manager::start()
{
    m_thread.setObjectName(robotName());
    m_component->moveToThread(&m_thread);

    qInfo() << "Starting" << m_thread.objectName() << "...";
    m_thread.start();
}

void SimpleRobot2Manager::stop()
{
    m_thread.requestInterruption();
    m_thread.quit();
    m_thread.wait();
}

