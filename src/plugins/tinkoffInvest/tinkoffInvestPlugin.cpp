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
#include "servicereply.h"

using namespace hevaa;

TinkoffComponent::TinkoffComponent(AppSettins &plugin_settings): CustomComponent(plugin_settings)
{
    qRegisterMetaType<ServiceReply>();
    setObjectName(COMPONENT_NAME_TINKOFF);
    m_greeter = QSharedPointer<InvestApiClient>::create(m_plugin_settings["TINKHOST"], m_plugin_settings["TINKPASS"]);
}

TinkoffComponent::~TinkoffComponent()
{

}

const hevaa::transport::Node TinkoffComponent::ComponentInfo()
{
    hevaa::transport::Row rootdata = {objectName()};
    auto root = hevaa::transport::Node::create(rootdata);
    auto commands = hevaa::transport::Node::create(TINKOFF_SERVISES);
    for (int i = 0; i < TINKOFF_SERVISES.count(); i++)
    {
        auto services = getServicesList(m_greeter, TINKOFF_SERVISES[i].toStringList()[0]);
        if (services.count() > 0)
        {
            auto buttons = hevaa::transport::Node::create(services);
            commands->appendChild(buttons);
        }
    }
    root->appendChild(commands);
    return root;
}

hevaa::transport::Row TinkoffComponent::getServicesList(const QSharedPointer<InvestApiClient> iap, const QString &prefix)
{
    return iap ? iap->getServiceMethods(prefix) : hevaa::transport::Row({});
}

void TinkoffComponent::handleData(const hevaa::transport::message &msg)
{
    CustomComponent::handleData(msg);
    try {
        if (msg.type() == hevaa::transport::Command)
        {
            qDebug() << "Sending request to tinkoff...";

            ServiceReply reply;
            QString func = msg.body()->data(0).toString();
            QString srv = msg.body()->data(1).toString();
            if (m_greeter->service(srv).get())
            {
                QMetaObject::invokeMethod(m_greeter->service(srv).get(),
                                      func.toStdString().c_str(),
                                      Qt::DirectConnection,
                                      Q_RETURN_ARG(ServiceReply, reply)
                                   );
                QString str = QString::fromStdString(reply.ptr()->DebugString());
                qDebug() << "Greeter received:" << str;
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
    return m_blankComponent;
}

void TinkoffManager::initModule(AppSettins &plugin_settings)
{
    m_blankComponent = QSharedPointer<TinkoffComponent>::create(plugin_settings);
}

void TinkoffManager::startModule()
{
    qDebug() << "The TinkoffManager thread is" << QThread::currentThread();

    m_blankThread.setObjectName(moduleName());
    m_blankComponent->moveToThread(&m_blankThread);

    connect(&m_blankThread, &QThread::started, [](){ qDebug() << "tinkoffThread send signal started!"; });
    connect(&m_blankThread, &QThread::finished, m_blankComponent.data(), [](){ qDebug() << "tinkoffThread send signal finished!"; });

    qInfo() << "Starting" << m_blankThread.objectName() << "...";
    m_blankThread.start();
}

void TinkoffManager::stopModule()
{
    m_blankThread.requestInterruption();
    m_blankThread.quit();
    m_blankThread.wait();
}

