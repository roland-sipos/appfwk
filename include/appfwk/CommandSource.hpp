/** @file CommandSource.hpp Provide a base class for sources of commands
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */
#ifndef DUNEDAQ_APPFWK_COMMANDSOURCE_HPP
#define DUNEDAQ_APPFWK_COMMANDSOURCE_HPP

#include <nlohmann/json.hpp>


namespace dunedaq::appfwk {

    /** @brief CommandSource provides abstract base class for a source of commands.
     *
     * An subclass shall override recv() to provide the next command
     * and may override send() to accept a reply object from the
     * application.  Callers shall expect either or both may block.
     *
     * Subclasses must have call to CPP macro:
     *
     *     DEFINE_DUNE_DAQ_COMMANDSOURCE(dunedaq::appfwk::MyCmdSrc)
     */
    class CommandSource {
      public:
        using object_t = nlohmann::json;

        /// Subclass must override to get a source URI.
        CommandSource(std::string uri) {}
        virtual ~CommandSource() {};

        /// Recieve the next command object.  Call may block indefinitely.
        virtual object_t recv() = 0;

        /// Send a reply object.  Call may block indefinitely.  
        virtual void send(object_t /*reply*/) { }
    };

    /** @brief Load a CommandSource plugin and return an instance to
     * source from the URI.
     */
    inline std::shared_ptr<CommandSource>
    makeCommandSource(std::string const& plugin_name, std::string const& uri)
    {
        static cet::BasicPluginFactory bpf("duneCommandSource", "make");
        return bpf.makePlugin<std::shared_ptr<CommandSource>>(plugin_name, uri);
    }

}

#define DEFINE_DUNE_DAQ_COMMANDSOURCE(klass)\
  extern "C" { std::shared_ptr<dunedaq::appfwk::CommandSource> make(std::string uri) \
  { return std::shared_ptr<dunedaq::appfwk::CommandSource>(new klass(uri)); }}

#endif
