#ifndef HEVAAPATHS_H
#define HEVAAPATHS_H

#include <QCoreApplication>
#ifdef Q_OS_WIN32
#include "WindowsStandardPaths.h"
#else
#include "LinuxStandardPaths.h"
#endif

struct StandardPaths
{
    enum HevaaStandardLocationType{
        ConfigHevaaLocation,
        DataHevaaLocation,
        LogHevaaLocation
    };

    static QFileDevice::Permissions getFullPermissions()
    {
        static const QFile::Permissions ownerPermissions = QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner;
        static const QFile::Permissions groupPermissions = QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup;
        static const QFile::Permissions otherPermissions = QFile::ReadOther | QFile::WriteOther | QFile::ExeOther;
        return ownerPermissions | groupPermissions | otherPermissions;
    }

    static void initPermissions()
    {
        QList<HevaaStandardLocationType> hevaaPaths = {ConfigHevaaLocation, DataHevaaLocation, LogHevaaLocation};
        for(auto type : hevaaPaths){
            QFile::setPermissions(hevaaStandardLocation(type), getFullPermissions());
        }
    }

    static QString hevaaStandardLocation(HevaaStandardLocationType type)
    {
        static QString basePath = Paths().DefaultBasePath();
        static QString logPath = Paths().LogsPath();
        switch (type) {
        case HevaaStandardLocationType::LogHevaaLocation:
            return logPath;
        case HevaaStandardLocationType::DataHevaaLocation:
            return basePath + "database";
        case HevaaStandardLocationType::ConfigHevaaLocation:
            return basePath + "config";
        default:
            return basePath;
        }
    }

private:
    // чтобы использовать static поле без его определения (header only library)
    // в cpp файле (c++17 c inline variable еще недоступен на GCC 6.3 и msvc 2015)
#ifdef Q_OS_WIN32
    static WindowsStandardPaths& Paths() {static WindowsStandardPaths paths; return paths;}
#else
    static LinuxStandardPaths& Paths() {static LinuxStandardPaths paths; return paths;}
#endif

};

#endif // HEVAAPATHS_H
