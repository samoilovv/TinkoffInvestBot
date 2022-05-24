#ifndef MODULE_INTERFACE
#define MODULE_INTERFACE

#include <QtPlugin>
#include "hevaa_common.h"
#include "customcomponent.h"

namespace hevaa {

    class ModuleInterface
    {
    public:
        virtual ~ModuleInterface() {}
        virtual QString moduleName() const = 0;
        virtual QSharedPointer<CustomComponent> getComponent() const = 0;
        virtual void initModule(AppSettins &plugin_settings) {Q_UNUSED(plugin_settings)}
        virtual void startModule() {}
        virtual void stopModule() {}
    };
}

#define ModuleInterface_iid "Hevaa.ModuleInterface/1.0"

Q_DECLARE_INTERFACE(hevaa::ModuleInterface, ModuleInterface_iid)

#endif // MODULE_INTERFACE
