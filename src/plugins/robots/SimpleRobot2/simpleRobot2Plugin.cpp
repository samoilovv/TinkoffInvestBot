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

//                QMetaObject::invokeMethod(m_client->service(srv.toStdString()).get(),
//                                      func.toStdString().c_str(),
//                                      Qt::DirectConnection,
//                                      Q_RETURN_ARG(ServiceReply, reply)
//                                   );

//                QString str = QString::fromStdString(reply.ptr()->DebugString());
//                qDebug() << "Received message:" << str;
//                hevaa::transport::message hm(hevaa::transport::Info, hevaa::transport::Node::create(hevaa::transport::Row{str}));
//                emit transmitData(hm);
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

QString SimpleRobot2Manager::moduleName() const
{
    return "Robot2";
}

QSharedPointer<CustomComponent> SimpleRobot2Manager::getComponent() const
{
    return m_component;
}

void SimpleRobot2Manager::initModule(AppSettins &plugin_settings)
{
    m_component = QSharedPointer<SimpleRobot2Component>::create(plugin_settings);
}

void SimpleRobot2Manager::startModule()
{
    qDebug() << "The TinkoffManager thread is" << QThread::currentThread();

    m_thread.setObjectName(moduleName());
    m_component->moveToThread(&m_thread);

    qInfo() << "Starting" << m_thread.objectName() << "...";
    m_thread.start();
}

void SimpleRobot2Manager::stopModule()
{
    m_thread.requestInterruption();
    m_thread.quit();
    m_thread.wait();
}

