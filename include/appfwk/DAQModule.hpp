/**
 * @file DAQModule.hpp DAQModule Class Interface
 *
 * The DAQModule interface defines the required functionality for all
 * DAQModules that use the Application Framework. DAQModules are
 * defined as "a set of code which performs a specific task". They may
 * be connected to one another within a DAQ Application by Queue
 * instances, in a graph defined by a ModuleList.  They may respond to
 * a named command (eg see @ref CcmCommands.hpp) by registering a
 * method as a command handler.
 *
 * This interface is intended to define only absolutely necessary methods to be
 * able to support the many different tasks that DAQModules will be asked to
 * perform.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef APPFWK_INCLUDE_APPFWK_DAQMODULE_HPP_
#define APPFWK_INCLUDE_APPFWK_DAQMODULE_HPP_

#include "appfwk/NamedObject.hpp"

#include <cetlib/BasicPluginFactory.h>
#include <cetlib/compiler_macros.h>
#include <ers/Issue.h>
#include <nlohmann/json.hpp>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#ifndef EXTERN_C_FUNC_DECLARE_START
#define EXTERN_C_FUNC_DECLARE_START \
  extern "C"                        \
  {
#endif

/**
 * @brief Declare the function that will be called by the plugin loader
 * @param klass Class to be defined as a DUNE DAQ Module
 */
#define DEFINE_DUNE_DAQ_MODULE(klass)                                 \
  EXTERN_C_FUNC_DECLARE_START                                         \
  std::shared_ptr<dunedaq::appfwk::DAQModule> make(std::string n)     \
  {                                                                   \
    return std::shared_ptr<dunedaq::appfwk::DAQModule>(new klass(n)); \
  }                                                                   \
  }

namespace dunedaq {

namespace appfwk {
/**
 * @brief The DAQModule class implementations are a set of code which performs
 * a specific task.
 *
 * This interface defines the basic methods which all DAQModules should expose.
 * Developers implementing DAQModules should feel free to use whatever Plugins
 * and Services are necessary to accomplish their needed functionality.
 *
 * This header also contains the definitions of the Issues that can be
 * thrown by the DAQModule.
 */
class DAQModule : public NamedObject
{
public:
  /**
   * @brief DAQModule Constructor
   * @param name Name of the DAQModule
   */
  explicit DAQModule(std::string name)
    : NamedObject(name)
  {}

  using data_t = nlohmann::json;

  /**
   * @brief Execute a named command on this DAQModule
   * @param cmd The command name
   * @param data Qualifying command data.
   * @return none
   *
   * execute_command is the single entry point for DAQProcess to pass
   * commands (eg, originating from CCM) to the DAQModule.
   * Non-accepted commands or failure should throw an ERS exception.
   */
  void execute_command(const std::string& name, data_t data);

  std::vector<std::string> get_commands() const;

  bool has_command(const std::string& name) const;

protected:

  /**
   * @brief Registers a module method to handle a command named `cmd`.
   */
  template<typename Child>
  void register_command(const std::string& name, void (Child::*f)(data_t cmddat));

private:
  using CommandMap_t = std::map<std::string, std::function<void(data_t cmddat)>>;
  CommandMap_t commands_;
};

/**
 * @brief Load a DAQModule plugin and return a shared_ptr to the contained
 * DAQModule class
 * @param plugin_name Name of the plugin, e.g. DebugLoggingDAQModule
 * @param instance_name Name of the returned DAQModule instance, e.g.
 * DebugLogger1
 * @return shared_ptr to created DAQModule instance
 */
inline std::shared_ptr<DAQModule>
makeModule(std::string const& plugin_name, std::string const& instance_name)
{
  static cet::BasicPluginFactory bpf("duneDAQModule", "make");

  return bpf.makePlugin<std::shared_ptr<DAQModule>>(plugin_name, instance_name);
}

} // namespace appfwk

/**
 * @brief A generic DAQModule ERS Issue
 */
ERS_DECLARE_ISSUE(appfwk,                 ///< Namespace
                  GeneralDAQModuleIssue,  ///< Issue class name
                  " DAQModule: " << name, ///< Message
                  ((std::string)name)     ///< Message parameters
)

/**
 * @brief Generic command ERS Issue
 */
ERS_DECLARE_ISSUE_BASE(appfwk,                        ///< Namespace
                       CommandIssue,                  ///< Type of the issue
                       appfwk::GeneralDAQModuleIssue, ///< Base class of the issue
                       " Command " << cmd,            ///< Log Message from the issue
                       ((std::string)name),           ///< Base class attributes
                       ((std::string)cmd))            ///< Attribute of this class

/**
 * @brief The CommandFailed DAQModule ERS Issue
 */
ERS_DECLARE_ISSUE_BASE(appfwk,                                ///< Namespace
                       CommandRegistrationFailed,             ///< Type of the Issue
                       appfwk::CommandIssue,                  ///< Base class of the Issue
                       "Command registration failed.",        ///< Log Message from the issue
                       ((std::string)cmd)((std::string)name), ///< Base class attributes
                       ERS_EMPTY                              ///< Attribute of this class
)

/**
 * @brief The UnknownCommand DAQModule ERS Issue
 */
ERS_DECLARE_ISSUE_BASE(appfwk,                                ///< Namespace
                       UnknownCommand,                        ///< Issue class name
                       appfwk::CommandIssue,                  ///< Base class of the issue
                       "Command is not recognised",           ///< Log Message from the issue
                       ((std::string)cmd)((std::string)name), ///< Base class attributes
                       ERS_EMPTY                              ///< Attribute of this class
)

/**
 * @brief The CommandFailed DAQModule ERS Issue
 */
ERS_DECLARE_ISSUE_BASE(appfwk,                                ///< Namespace
                       CommandFailed,                         ///< Type of the Issue
                       appfwk::CommandIssue,                  ///< Base class of the Issue
                       "Command Failed. Reason " << reason,   ///< Log Message from the issue
                       ((std::string)cmd)((std::string)name), ///< Base class attributes
                       ((std::string)reason)                  ///< Attribute of this class
)

} // namespace dunedaq

#include "detail/DAQModule.hxx"

#endif // APPFWK_INCLUDE_APPFWK_DAQMODULE_HPP_


// Local Variables:
// c-basic-offset: 2
// End:
