/**
 * @file CcmInterface.hpp Interface to CCM
 *
 * CCM may provide commands to DAQProcess which may dispatch them to
 * registered command handers provided by instances of DAQModule.  The
 * interface to CCM specifies a set of command names as strings of
 * canonical spelling, a generic dynamic object and a templated mixin
 * class to assist in connecting fully typed command handlers.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */
#ifndef APPFWK_INCLUDE_APPFWK_CANONICALCOMMANDS_HPP_
#define APPFWK_INCLUDE_APPFWK_CANONICALCOMMANDS_HPP_

#include <nlohmann/json.hpp>

namespace dunedaq {

// This may one day move to a "ccm" package?
namespace appfwk {

    namespace command {

        /** Every command provides data which may qualify the command.
         * The data is dynamically typed according to the command name
         * and in some cases the expected recipient. 
         */
        using data_t = nlohmann::json;

        /** What follows are representations of the possible CCM
         * commands that a DAQ process may expect to receive over its
         * life cycle.  For each command, and after it is successfully
         * the processes is assumed to enter a described STATE.
         *
         * Note, each command is a type, not an instance in order to
         * facilitiate use in finite state machines and to use the
         * names in constexpr contexts.
         */

        /** The "init" command.  The process receives sufficient info
         * to construct any internal structure and if successful
         * becomes INITIALIZED.
         */
        struct Init {
            static constexpr char const* name = "init";
            data_t data;
        };

        /** The "conf" command.  The process receives and applies configuration
         * information and becomes CONFIGURED.
         */
        struct Conf {
            static constexpr char const* name = "conf";
            data_t data;
        };

        /** The "start" command.  The process receives parameters
         * required to initiate nominal operation (eg, "run" number)
         * and becomes RUNNING.
         */
        struct Start {
            static constexpr char const* name = "start";
            data_t data;
        };

        /** The "stop" command.  The process undoes what was done in
         * response to a previous "start" command and returns to CONFIGURED.
         */
        struct Stop {
            static constexpr char const* name = "stop";
            data_t data;
        };

        /** The "scrap" command.  The process undoes what was done in
         * response to the previous "conf" command and returns to
         * INITIALIZED.
         */
        struct Scrap {
            static constexpr char const* name = "scrap";
            data_t data;
        };

        /** The "fina" command.  The process undoes what was done in
         * response to the previous "init" command and becomes READY".
         */
        struct Fina {
            static constexpr char const* name = "fina";
            data_t data;
        };

        /** The "exec" command.  A process should execute (run) one or
         * more other processes as described in the data_t.  The (sub)
         * processes that are executed become in the DEFAULT state.
         */
        struct Exec {
            static constexpr char const* name = "exec";
            data_t data;
        };

        /** The "term" command.  A process should terminate (kill) one
         * or more processes, including potentialy itself as described
         * in the data_t.  
         */
        struct Term {
            static constexpr char const* name = "term";
            data_t data;
        };

} // namespace command

} // namespace appfwk

} // namespace dunedaq


#endif

// Local Variables:
// c-basic-offset: 2
// End:
