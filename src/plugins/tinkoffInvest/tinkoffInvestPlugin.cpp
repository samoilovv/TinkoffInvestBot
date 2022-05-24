#include <QDebug>
#include <QCoreApplication>
#include <QMetaMethod>
#include "hevaa_consts.h"
#include "hevaa_transport.h"
#include "hevaa_tree.h"
#include "tinkoffInvestPlugin.h"
#include "tinkoffInvestConsts.h"
#include "customservice.h"
#include "sandboxservice.h"
#include "usersservice.h"
#include "commontypes.h"

using namespace hevaa;

TinkoffComponent::TinkoffComponent(AppSettins &plugin_settings): CustomComponent(plugin_settings)
{
    setObjectName(COMPONENT_NAME_TINKOFF);
    m_client = QSharedPointer<InvestApiClient>::create(m_plugin_settings["TINKHOST"].toStdString(), m_plugin_settings["TINKTOKEN"].toStdString());
}

TinkoffComponent::~TinkoffComponent()
{

}

const hevaa::transport::Node TinkoffComponent::ComponentInfo()
{
    hevaa::transport::Row rootdata = {objectName()};
    auto root = hevaa::transport::Node::create(rootdata);
    auto commands = hevaa::transport::Node::create(TINKOFF_SERVISES);
    root->appendChild(commands);
    return root;
}

void TinkoffComponent::handleData(const hevaa::transport::message &msg)
{
    CustomComponent::handleData(msg);
    try {
        if (msg.type() == hevaa::transport::Command)
        {
            qDebug() << "Sending request to tinkoff...";

            QString func = msg.body()->data(0).toString();
            QString srv = msg.body()->data(1).toString();          
            QString GetAccounts = "GetAccounts";
            if (srv == "info")
            {
                auto userservice = std::dynamic_pointer_cast<Users>(m_client->service("users"));
                ServiceReply reply = userservice->GetAccounts();
                QString str = QString::fromStdString(reply.ptr()->DebugString());
                qDebug() << "Received message:" << str;
                hevaa::transport::message hm(hevaa::transport::Info, hevaa::transport::Node::create(hevaa::transport::Row{str}));
                emit transmitData(hm);
            } else
            {
                qDebug() << "There is no such service:" << srv;
            }
        }
    } catch (std::exception& e) {
         qCritical() << QString("error: %1").arg(e.what());
    }
}

TinkoffManager::~TinkoffManager()
{

}

QString TinkoffManager::moduleName() const
{
    return MODULE_NAME_TINKOFF;
}

QSharedPointer<CustomComponent> TinkoffManager::getComponent() const
{
    return m_component;
}

void TinkoffManager::initModule(AppSettins &plugin_settings)
{
    m_component = QSharedPointer<TinkoffComponent>::create(plugin_settings);
}

void TinkoffManager::startModule()
{
    qDebug() << "The TinkoffManager thread is" << QThread::currentThread();

    m_thread.setObjectName(moduleName());
    m_component->moveToThread(&m_thread);

    qInfo() << "Starting" << m_thread.objectName() << "...";
    m_thread.start();
}

void TinkoffManager::stopModule()
{
    m_thread.requestInterruption();
    m_thread.quit();
    m_thread.wait();
}

