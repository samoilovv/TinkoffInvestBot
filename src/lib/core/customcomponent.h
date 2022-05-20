#ifndef CUSTOMCOMPONENT_H
#define CUSTOMCOMPONENT_H

#include <QObject>
#include <QTimer>
#include "hevaa_common.h"
#include "hevaa_message.h"
#include "hevaa_tree.h"

/*!
    \brief Базовый класс для создания компонентов программы

    Содержить в себе все необходимые поля и методы для создания основных модулей программы,
    таких как телеграм бот, менеджер упраления базами данных или торговый робот.
*/
class CustomComponent: public QObject
{
    Q_OBJECT

private:
    int m_timerId;

protected:
    /// Основные настройки
    const AppSettins m_plugin_settings;
    /// Информация, которую необходимо передать другому компоненту
    virtual const hevaa::transport::Node ComponentInfo();
    /// Осуществлять по таймеру попытки соединиться с другим компонентом
    virtual void timerEvent(QTimerEvent *);

public:
    explicit CustomComponent(QObject *parent = nullptr);
    CustomComponent(const AppSettins &plugin_settings, QObject *parent = nullptr);

signals:
    /// Передать сообшение в другой модуль
    void transmitData(const hevaa::transport::message &);

public slots:
    /// Первоначальная инициализация компонента
    virtual void init(const hevaa::transport::message &msg);
    /// Прием сообщений от других модулей программы
    virtual void handleData(const hevaa::transport::message &msg);

};

#endif // CUSTOMCOMPONENT_H
