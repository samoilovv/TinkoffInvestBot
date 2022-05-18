#include <QCoreApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QDebug>
#include <QCommandLineParser>
#include "HevaaApplication.h"
#include "hevaa_consts.h"

int main(int argc, char *argv[])
{
    QSystemSemaphore qss(hevaa::APP_UNIQUE_SEMAPHORE, 1);
    qss.acquire();
    {
        QSharedMemory qsm(hevaa::APP_UNIQUE_NAME);
        qsm.attach();
    }
    QSharedMemory qsm(hevaa::APP_UNIQUE_NAME);
    bool isRunning = qsm.attach();
    if (!isRunning) {
        qsm.create(1);
    }
    qss.release();
    if(isRunning) {
        qFatal("The app already started");
    }
    HevaaApplication app(argc, &argv);
    QCommandLineParser parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.setApplicationDescription("Robot manager for TinkoffInvest");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    app.init();
    return app.exec();
}
