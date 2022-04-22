#include <QDebug>
#include <QCoreApplication>

#include "hevaa_consts.h"
#include "blankPlugin.h"

using namespace hevaa;

BlankComponent::BlankComponent(AppSettins &plugin_settings): CustomComponent(plugin_settings)
{
    setObjectName(COMPONENT_NAME_BLANK);
    qDebug() << objectName() << "created and timer started!";
}

BlankComponent::~BlankComponent()
{

}

BlankManager::~BlankManager()
{

}

QString BlankManager::moduleName() const
{
    return MODULE_NAME_BLANK;
}

QSharedPointer<CustomComponent> BlankManager::getComponent() const
{
    return m_blankComponent;
}

void BlankManager::initModule(AppSettins &plugin_settings)
{
    m_blankComponent = QSharedPointer<BlankComponent>::create(plugin_settings);
}

void BlankManager::startModule()
{
    qDebug() << "The BlankManager thread is" << QThread::currentThread();

    m_blankThread.setObjectName(moduleName());
    m_blankComponent->moveToThread(&m_blankThread);

    connect(&m_blankThread, &QThread::started, [](){ qDebug() << "blankThread send signal started!"; });
    connect(&m_blankThread, &QThread::finished, m_blankComponent.data(), [](){ qDebug() << "blankThread send signal finished!"; });

    qInfo() << "Starting" << m_blankThread.objectName() << "...";
    m_blankThread.start();
}

void BlankManager::stopModule()
{
    qDebug() << "BlankManager stopModule";

    m_blankThread.requestInterruption();
    m_blankThread.quit();
    m_blankThread.wait();
}

