#include <QMetaMethod>
#include "customcomponent.h"
#include "hevaa_message.h"
#include "hevaa_transport.h"

const hevaa::transport::Node CustomComponent::ComponentInfo()
{
    return hevaa::transport::Node::create(hevaa::transport::Row{objectName()});
}

void CustomComponent::timerEvent(QTimerEvent *)
{
    static const QMetaMethod transmitDataSignal = QMetaMethod::fromSignal(&CustomComponent::transmitData);
    if (isSignalConnected(transmitDataSignal)) {
        qDebug() << objectName() << "Stop timer and is trying to connect...";
        killTimer(m_timerId);
        hevaa::transport::message msg(hevaa::transport::HandshakeQuery);
        emit transmitData(msg);
    }
}

CustomComponent::CustomComponent(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<hevaa::transport::message>();
}

CustomComponent::CustomComponent(const AppSettins &plugin_settings, QObject *parent) :
    QObject(parent),
    m_plugin_settings(plugin_settings)
{
    qRegisterMetaType<hevaa::transport::message>();
    m_timerId = startTimer(1000);
}

void CustomComponent::handleData(const hevaa::transport::message &msg)
{
    if (msg.type() == hevaa::transport::HandshakeAnswer)
    {
        qDebug() << objectName() << "was connected to" << msg.body()->data(0).toString();
    }
    if (msg.type() == hevaa::transport::HandshakeQuery)
    {
        hevaa::transport::message msg(hevaa::transport::HandshakeAnswer, ComponentInfo());
        emit transmitData(msg);
    }
}


