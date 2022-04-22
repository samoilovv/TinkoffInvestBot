#ifndef CUSTOMCOMPONENT_H
#define CUSTOMCOMPONENT_H

#include <QObject>
#include <QTimer>

#include "hevaa_common.h"
#include "hevaa_message.h"
#include "hevaa_tree.h"

class CustomComponent: public QObject
{
    Q_OBJECT

private:
    int m_timerId;

protected:
    const AppSettins m_plugin_settings;

    virtual const hevaa::transport::Node ComponentInfo();
    virtual void timerEvent(QTimerEvent *); //для передачи хэндшейков

public:
    explicit CustomComponent(QObject *parent = nullptr);
    CustomComponent(const AppSettins &plugin_settings, QObject *parent = nullptr);

signals:
    void transmitData(const hevaa::transport::message &);

public slots:
    virtual void handleData(const hevaa::transport::message &msg);

};

#endif // CUSTOMCOMPONENT_H
