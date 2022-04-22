#ifndef HEVAA_COMMON_H
#define HEVAA_COMMON_H

#include <QObject>
#include <QMap>
#include <QMetaType>

using AppSettins = QMap<QString, QString>;
using ModulesList = QMap<QString, QObject *>;

#endif // HEVAA_COMMON_H
