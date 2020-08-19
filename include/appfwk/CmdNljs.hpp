/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK__CMD_CMD_NLJS_HPP
#define DUNEDAQ__APPFWK__CMD_CMD_NLJS_HPP

#include "CmdStructs.hpp"
#include <nlohmann/json.hpp>


namespace dunedaq::appfwk::cmd {

    using json = nlohmann::json;

    NLOHMANN_JSON_SERIALIZE_ENUM( Id, {
            { dunedaq::appfwk::cmd::Id::exec, "exec" },
            { dunedaq::appfwk::cmd::Id::init, "init" },
            { dunedaq::appfwk::cmd::Id::conf, "conf" },
            { dunedaq::appfwk::cmd::Id::start, "start" },
            { dunedaq::appfwk::cmd::Id::stop, "stop" },
            { dunedaq::appfwk::cmd::Id::scrap, "scrap" },
            { dunedaq::appfwk::cmd::Id::fini, "fini" },
            { dunedaq::appfwk::cmd::Id::term, "term" },
            { dunedaq::appfwk::cmd::Id::undef, "undef" },
        })

    // Converters for Payload
    // Associate data to a recipient
    inline void to_json(json& j, const Payload& obj) {
        j["recipient"] = obj.recipient;
        j["data"] = obj.data;
    }
    inline void from_json(const json& j, Payload& obj) {
        if (j.contains("recipient")) {
            j.at("recipient").get_to(obj.recipient);
        }
        if (j.contains("data")) {
            obj.data = j.at("data");
        }
    }
    // Converters for Object
    // A command to a process
    inline void to_json(json& j, const Object& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Object& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Exec
    // FSM event type for command Exec
    inline void to_json(json& j, const Exec& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Exec& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Init
    // FSM event type for command Init
    inline void to_json(json& j, const Init& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Init& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Conf
    // FSM event type for command Conf
    inline void to_json(json& j, const Conf& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Conf& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Start
    // FSM event type for command Start
    inline void to_json(json& j, const Start& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Start& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Stop
    // FSM event type for command Stop
    inline void to_json(json& j, const Stop& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Stop& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Scrap
    // FSM event type for command Scrap
    inline void to_json(json& j, const Scrap& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Scrap& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Fini
    // FSM event type for command Fini
    inline void to_json(json& j, const Fini& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Fini& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Term
    // FSM event type for command Term
    inline void to_json(json& j, const Term& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Term& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }
    // Converters for Undef
    // FSM event type for command Undef
    inline void to_json(json& j, const Undef& obj) {
        j["id"] = obj.id;
        j["payload"] = obj.payload;
    }
    inline void from_json(const json& j, Undef& obj) {
        if (j.contains("id")) {
            j.at("id").get_to(obj.id);
        }
        if (j.contains("payload")) {
            j.at("payload").get_to(obj.payload);
        }
    }


} // namespace dunedaq::appfwk::cmd

#endif // DUNEDAQ__APPFWK__CMD_CMD_NLJS_HPP