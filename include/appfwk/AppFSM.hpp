#ifndef DUNEDAQ_APPFWK_APPFSM_HPP
#define DUNEDAQ_APPFWK_APPFSM_HPP

#include <boost/msm/front/state_machine_def.hpp>
#include <nlohmann/json.hpp>

// Provides FSM events
#include "appfwk/CmdStructs.hpp"

namespace dunedaq::appfwk {

    /** @brief Abstract MSM FSM front end.
     *
     * Inherit from this class (say class name "MyFE") and provide handle_*().
     *
     * Then do:
     * #include <boost/msm/back/state_machine.hpp>
     * using MyFSM = boost::msm::back::state_machine<MyFE>;
     *
     * MyFSM sm;
     * sm.process_event(....);
     */
    struct AppFSMFE : public boost::msm::front::state_machine_def<AppFSMFE> {

        virtual ~AppFSMFE() {}

        using object_t = nlohmann::json;

        /// FSM States

        /// The process is a blank slate.
        struct Ready : public boost::msm::front::state<> { };

        /// The process structure is constructed.
        struct Initialized : public boost::msm::front::state<> { };

        /// The process is configured
        struct Configured : public boost::msm::front::state<> { };

        /// The process is operating.
        struct Running : public boost::msm::front::state<> { };
    
        using initial_state = Ready;

        /// Actions 
        virtual void handle_init(const cmd::Init& evt) = 0;
        virtual void handle_conf(const cmd::Conf& evt) = 0;
        virtual void handle_start(const cmd::Start& evt) = 0;
        virtual void handle_stop(const cmd::Stop& evt) = 0;
        virtual void handle_scrap(const cmd::Scrap& evt) = 0;
        virtual void handle_fina(const cmd::Fina& evt) = 0;

        using fe = AppFSMFE;    // shorthand
        // clang-format off
        struct transition_table : boost::mpl::vector<
            //    Start     Event         Next           Action           Guard
            a_row<Ready,       cmd::Init,  Initialized, &fe::handle_init>,
            a_row<Initialized, cmd::Conf,  Configured,  &fe::handle_conf>,
            a_row<Configured,  cmd::Start, Running,     &fe::handle_start>,
            a_row<Running,     cmd::Stop,  Configured,  &fe::handle_stop>,
            a_row<Configured,  cmd::Scrap, Initialized, &fe::handle_scrap>,
            a_row<Initialized, cmd::Fina,  Ready,       &fe::handle_fina>
            > {};
        // clang-format on
    };
    // using AppFSM = boost::msm::back::state_machine<AppFSMFE>;

    
}

#endif
