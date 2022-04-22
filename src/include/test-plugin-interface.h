#ifndef TEST_PLUGIN_INTERFACE
#define TEST_PLUGIN_INTERFACE
#include <QtPlugin>

namespace hevaa {

    class TestPluginInterface
    {
    public:
        virtual ~TestPluginInterface() {}
        virtual void doSomething() const = 0;
    };

}

#define TestPluginInterface_iid "whatever.you.want.TestPluginInterface"

Q_DECLARE_INTERFACE(hevaa::TestPluginInterface, TestPluginInterface_iid)

#endif // TEST_PLUGIN_INTERFACE
