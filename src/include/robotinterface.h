#ifndef I_MODULE_PLUGIN
#define I_MODULE_PLUGIN

#include <QtPlugin>
#include "hevaa_common.h"
#include "customcomponent.h"

namespace hevaa {

    class IModulePlugin
    {
    public:
        virtual ~IModulePlugin() {}
        virtual QString moduleName() const = 0;
        virtual QSharedPointer<CustomComponent> getComponent() const = 0;
        virtual void initModule(AppSettins &plugin_settings) {Q_UNUSED(plugin_settings)}
        virtual void startModule() {}
        virtual void stopModule() {}
    };
}

#define HevaaModulePluginInterface_iid "Hevaa.HevaaModulePlugin/1.0"

Q_DECLARE_INTERFACE(hevaa::IModulePlugin, HevaaModulePluginInterface_iid)

#endif // I_MODULE_PLUGIN
