#ifndef MAIN_HEVAAAPPLICATION_H
#define MAIN_HEVAAAPPLICATION_H

#include <QCoreApplication>
#include <QSharedPointer>
#include "pluginsloader.h"
#include "worker.h"
#include "hevaa_common.h"

class HevaaApplication : public QCoreApplication
{
    Q_OBJECT

public:
    HevaaApplication(int& argc, char **argv[]);
    ~HevaaApplication() = default;
    void init(QString psw = "");

private:
    QString password;
    QSharedPointer<PluginsLoader> m_pluginsLoader;
    QSharedPointer<workerManager> WManager;
};

#endif // MAIN_HEVAAAPPLICATION_H

