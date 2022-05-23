#include <QDebug>
#include <QCoreApplication>
#include <QtSql/QSqlQuery>
#include <QDateTime>
#include "hevaa_consts.h"
#include "dataBasePlugin.h"

using namespace hevaa;

DataBaseWriter::DataBaseWriter(AppSettins &plugin_settings): CustomComponent(plugin_settings)
{
    setObjectName(COMPONENT_NAME_DATABASE);
    try {
        m_db = QSqlDatabase::addDatabase("QPSQL");
        m_db.setHostName(plugin_settings["DBHOST"]);
        m_db.setDatabaseName(plugin_settings["DBNAME"]);
        m_db.setUserName(plugin_settings["DBUSER"]);
        m_db.setPassword(plugin_settings["DBPASS"]);
        QSqlQuery query(m_db);
        if (m_db.open())
        {
            qDebug() << "Database connection successful";
        } else {
            qDebug() << "Failed to connect to database";
        }
    } catch (std::exception& e) {
         qCritical() << QString("error: %1").arg(e.what());
    }
    qDebug() << objectName() << "created and timer started!";

}

DataBaseWriter::~DataBaseWriter()
{
    m_db.close();
}

void DataBaseWriter::handleData(const hevaa::transport::message &msg)
{
    CustomComponent::handleData(msg);
    qDebug() << "The DataBaseWriter::handleData thread is" << QThread::currentThread();
    try {
        if (m_db.isOpen())
        {
            auto m = msg.body()->data(0).toStringList();
            QSqlQuery query(m_db);

            QDateTime timestamp = QDateTime::currentDateTime();
            query.prepare("INSERT INTO he_raw (user_name, raw_msg, msg_datetime) VALUES (?, ?, ?)");
            query.addBindValue(m[0]);
            query.addBindValue(m[1]);
            query.addBindValue(timestamp);
            query.exec();
        }
    } catch (std::exception& e) {
         qCritical() << QString("error: %1").arg(e.what());
    }
}

DataBaseManager::~DataBaseManager()
{

}

QString DataBaseManager::moduleName() const
{
    return MODULE_NAME_DATABASE;
}

QSharedPointer<CustomComponent> DataBaseManager::getComponent() const
{
    return m_dataBaseWriter;
}

void DataBaseManager::initModule(AppSettins &plugin_settings)
{
    m_dataBaseWriter = QSharedPointer<DataBaseWriter>::create(plugin_settings);
}

void DataBaseManager::startModule()
{
    qDebug() << "The DataBaseManager thread is" << QThread::currentThread();

    m_dataBaseThread.setObjectName(moduleName());
    m_dataBaseWriter->moveToThread(&m_dataBaseThread);

    connect(&m_dataBaseThread, &QThread::started, [](){ qDebug() << "dataBaseThread send signal started!"; });
    connect(&m_dataBaseThread, &QThread::finished, m_dataBaseWriter.data(), [](){ qDebug() << "dataBaseThread send signal finished!"; });

    qInfo() << "Starting" << m_dataBaseThread.objectName() << "...";
    m_dataBaseThread.start();
}

void DataBaseManager::stopModule()
{
    m_dataBaseThread.requestInterruption();
    m_dataBaseThread.quit();
    m_dataBaseThread.wait();
}

