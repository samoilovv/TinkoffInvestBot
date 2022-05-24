#ifndef ROBOT_INTERFACE
#define ROBOT_INTERFACE

#include <QtPlugin>
#include "hevaa_common.h"
#include "customcomponent.h"

namespace hevaa {

    class RobotInterface
    {
    public:
        virtual ~RobotInterface() {}
        virtual QString robotName() const = 0;
        virtual QSharedPointer<CustomComponent> getComponent() const = 0;
        virtual void init(AppSettins &plugin_settings) {Q_UNUSED(plugin_settings)}
        virtual void start() {}
        virtual void stop() {}
    };
}

#define RobotInterface_iid "Hevaa.RobotInterface/1.0"

Q_DECLARE_INTERFACE(hevaa::RobotInterface, RobotInterface_iid)

#endif // ROBOT_INTERFACE
