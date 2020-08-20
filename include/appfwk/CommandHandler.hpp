#ifndef DUNEDAQ_APPFWK_COMMANDHANDLER_HPP
#define DUNEDAQ_APPFWK_COMMANDHANDLER_HPP

#include <cetlib/BasicPluginFactory.h>
#include <nlohmann/json.hpp>

namespace dunedaq::appfwk {

    class CommandHandler {
      public:
        using pointer = std::shared_ptr<CommandHandler>;

        using object_t = nlohmann::json;

        CommandHandler(std::string name) {}
        virtual ~CommandHandler() {}
        virtual object_t handle(object_t cmdobj) = 0;
    };

    /** @brief Load a CommandHandler plugin and return an instance.
     */
    inline std::shared_ptr<CommandHandler>
    makeCommandHandler(std::string const& plugin_name, std::string const& inst)
    {
        static cet::BasicPluginFactory bpf("duneCommandHandler", "make");
        return bpf.makePlugin<std::shared_ptr<CommandHandler>>(plugin_name, inst);
    }

}



#endif
