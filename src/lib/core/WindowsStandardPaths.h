#ifndef WINDOWSSTANDARDPATHS_H
#define WINDOWSSTANDARDPATHS_H

#include <QDir>
#include <QSysInfo>


struct WindowsStandardPaths
{
    QString DefaultBasePath() const
    {
        auto winVersion = QSysInfo::windowsVersion();
        bool isWinXpOr2000 = (winVersion == QSysInfo::WV_XP) || (winVersion == QSysInfo::WV_2000);
        if(isWinXpOr2000) {
            static QString configPath(QDir::rootPath() + "Documents and Settings" +
                                      QDir::separator() + "All Users" + QDir::separator() +
                                      "hevaa" + QDir::separator());
            return configPath;
        }
        else {
            static QString configPath(QDir::rootPath() + "ProgramData"
                                      + QDir::separator() + "hevaa" + QDir::separator());
            return configPath;
        }
    }

    QString LogsPath() const
    {
        auto winVersion = QSysInfo::windowsVersion();
        bool isWinXpOr2000 = (winVersion == QSysInfo::WV_XP) || (winVersion == QSysInfo::WV_2000);
        if(isWinXpOr2000) {
            static QString configPath(QDir::rootPath() + "Documents and Settings" +
                                      QDir::separator() + "All Users" + QDir::separator() +
                                      "hevaa" + QDir::separator() + "log" + QDir::separator());
            return configPath;
        }
        else {
            static QString configPath(QDir::rootPath() + "ProgramData"
                                      + QDir::separator() + "hevaa" + QDir::separator()
                                      + "log" + QDir::separator());
            return configPath;
        }
    }
};

#endif // WINDOWSSTANDARDPATHS_H
