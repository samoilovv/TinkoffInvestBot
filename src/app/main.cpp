#include <QCoreApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QDebug>
#include <QCommandLineParser>
#include "HevaaApplication.h"

static const QString SINGLE_APPLICATION_UNIQUE_SEMAPHORE = "Hevaa unique sync name";
static const QString SINGLE_APPLICATION_UNIQUE_NAME = "Hevaa unique single apllication name";

int main(int argc, char *argv[])
{
    //---------------
    QSystemSemaphore sema(SINGLE_APPLICATION_UNIQUE_SEMAPHORE, 1);
    // Проверка на единственность запущенного экземпляра
    sema.acquire();
    {
        QSharedMemory shmem(SINGLE_APPLICATION_UNIQUE_NAME);
        shmem.attach();
    }
    QSharedMemory shmem(SINGLE_APPLICATION_UNIQUE_NAME);
    bool isRunning = shmem.attach();
    if(!isRunning) {
        shmem.create(1);
    }
    sema.release();
    if(isRunning) {
        qFatal("Application already started");
    }
    //----------------
    HevaaApplication app(argc, &argv);
    QCommandLineParser parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.setApplicationDescription("Описание программы Hevaa");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("password", "Пароль для декодирования настроек подключения к БД");
    parser.process(app);

    const QStringList args(parser.positionalArguments());
    args.size() < 2 ? app.init() : app.init(args.at(1));
    return app.exec();
}
