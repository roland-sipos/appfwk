#ifndef DUNEDAQ::APPFWK::CCM_CCM_NLJS_HPP
#define DUNEDAQ::APPFWK::CCM_CCM_NLJS_HPP



#include <nlohmann/json.hpp>

namespace dunedaq::appfwk::ccm {

    using json = nlohmann::json;

    NLOHMANN_JSON_SERIALIZE_ENUM( CommandName, {
            { dunedaq::appfwk::ccm::CommandName::exec, "exec" },
            { dunedaq::appfwk::ccm::CommandName::init, "init" },
            { dunedaq::appfwk::ccm::CommandName::conf, "conf" },
            { dunedaq::appfwk::ccm::CommandName::start, "start" },
            { dunedaq::appfwk::ccm::CommandName::stop, "stop" },
            { dunedaq::appfwk::ccm::CommandName::scrap, "scrap" },
            { dunedaq::appfwk::ccm::CommandName::fini, "fini" },
            { dunedaq::appfwk::ccm::CommandName::term, "term" },
            { dunedaq::appfwk::ccm::CommandName::undef, "undef" },
        })

    // Converters for CommandPayload
    // Associate data to a recipient
    inline void to_json(json& j, const CommandPayload& obj) {
        j["recipient"] = obj.recipient;
        j["data"] = obj.data;
    }
    inline void from_json(const json& j, CommandPayload& obj) {
        if (j.contains("recipient"))
            j.at("recipient").get_to(obj.recipient);    
        if (j.contains("data"))
            j.at("data").get_to(obj.data);    
    }
    // Converters for Command
    // A CCM command to a process
    inline void to_json(json& j, const Command& obj) {
        j["name"] = obj.name;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Command& obj) {
        if (j.contains("name"))
            j.at("name").get_to(obj.name);    
        if (j.contains("payload"))
            j.at("payload").get_to(obj.payload);    
    }


} // namespace dunedaq::appfwk::ccm

#endif