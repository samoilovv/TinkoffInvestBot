#ifndef DATABASE_H
#define DATABASE_H

#include <QThread>
#include <QSharedPointer>
#include <QtSql/QSqlDatabase>
#include "imoduleplugin.h"
#include "customcomponent.h"

/*!
    \brief Провайдер базы данных
*/
class DataBaseWriter: public CustomComponent
{
Q_OBJECT

private:
    QSqlDatabase m_db;

public:
    DataBaseWriter(AppSettins &plugin_settings);
    ~DataBaseWriter();

public:
    void handleData(const hevaa::transport::message &msg) final;

};

/*!
    \brief Менеджер базы данных
*/
class DataBaseManager: public QObject, public hevaa::IModulePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.Hevaa.DataBasePlugin.1.0" FILE "dataBasePlugin.json")
    Q_INTERFACES(
            hevaa::IModulePlugin
            )

public:
    explicit DataBaseManager() = default;
    ~DataBaseManager();

    QString moduleName() const override;
    QSharedPointer<CustomComponent> getComponent() const override;
    void initModule(AppSettins &plugin_settings) override;
    void startModule() override;
    void stopModule() override;

private:
    QThread m_dataBaseThread;
    QSharedPointer<DataBaseWriter> m_dataBaseWriter;
};

#endif // DATABASE_H
