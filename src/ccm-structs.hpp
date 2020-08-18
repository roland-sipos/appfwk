
#ifndef DUNEDAQ__APPFWK__CCM_CCM_STRUCTS_HPP
#define DUNEDAQ__APPFWK__CCM_CCM_STRUCTS_HPP


#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace dunedaq::appfwk::ccm {

    /// @brief The set of command names which may be expected from CCM
    enum class CommandName: unsigned {
        exec,
        init,
        conf,
        start,
        stop,
        scrap,
        fini,
        term,
        undef,
    };

    // @brief 
    using CommandData = nlohmann::json;

    /// @brief Associate data to a recipient
    struct CommandPayload {
        std::string recipient;
        CommandData data;
    };


    /// @brief A CCM command to a process
    struct Command {
        CommandName name;
        std::vector<CommandPayload> payload;
    };


} // namespace dunedaq::appfwk::ccm

#endif // DUNEDAQ__APPFWK__CCM_CCM_STRUCTS_HPP