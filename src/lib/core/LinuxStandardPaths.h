#ifndef LINUXSTANDARDPATHS_H
#define LINUXSTANDARDPATHS_H

#include <QDir>
struct LinuxStandardPaths
{
    QString DefaultBasePath() const
    {
        static QString configPath = InitPath();
        return configPath;
    }

    QString LogsPath() const
    {
        QString defaultBasePath("/var/log/hevaa/");
        QString alternativeBasePath = QDir::homePath() + "/hevaa/log/";

        QDir defDir(defaultBasePath);
        QDir altDir(alternativeBasePath);

        // первым делом проверяем доступ к /var/hevaa/
        if(defDir.exists() || defDir.mkpath(defaultBasePath)) {
            QFileInfo info(defaultBasePath);
            if(info.isWritable() && info.isReadable())
                return defaultBasePath;
        }

        // в случае неудачи откатываемся к домашнему каталогу
        return alternativeBasePath;
    }

private:
    QString InitPath() const {
        QString defaultBasePath("/var/hevaa/");
        QString alternativeBasePath = QDir::homePath() + "/hevaa/";

        QDir defDir(defaultBasePath);
        QDir altDir(alternativeBasePath);

        // первым делом проверяем доступ к /var/hevaa/
        if(defDir.exists() || defDir.mkpath(defaultBasePath)) {
            QFileInfo info(defaultBasePath);
            if(info.isWritable() && info.isReadable())
                return defaultBasePath;
        }

        // в случае неудачи откатываемся к домашнему каталогу
        return alternativeBasePath;
    }
};

#endif // LINUXSTANDARDPATHS_H
