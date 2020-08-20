#ifndef DUNEDAQ_APPFWK_APPLICATION_HPP
#define DUNEDAQ_APPFWK_APPLICATION_HPP

#include "appfwk/CommandHandler.hpp"
#include "appfwk/AppFSM.hpp"
#include <boost/msm/back/state_machine.hpp>

namespace dunedaq::appfwk {

    class Application : public CommandHandler, public AppFSMFE {
        std::vector<CommandHandler::pointer> pipeline_;

      public:

        using object_t = nlohmann::json;

        Application(std::string name);
        virtual ~Application();

        // CommandHandler
        virtual object_t handle(object_t cmdobj) { return cmdobj; };


        virtual void handle_init(const cmd::Init& evt) {};
        virtual void handle_conf(const cmd::Conf& evt) {};
        virtual void handle_start(const cmd::Start& evt) {};
        virtual void handle_stop(const cmd::Stop& evt) {};
        virtual void handle_scrap(const cmd::Scrap& evt) {};
        virtual void handle_fina(const cmd::Fina& evt) {};

        /// Add to the pipeline structure.
        void append(CommandHandler::pointer cd);

    };
    using AppFSM = boost::msm::back::state_machine<Application>;
}



#endif
