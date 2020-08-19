/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK_TEST_NLJS_HPP
#define DUNEDAQ__APPFWK_TEST_NLJS_HPP

#include "TestStructs.hpp"
#include <nlohmann/json.hpp>


namespace dunedaq::appfwk {

    using json = nlohmann::json;


    // Converters for FakeDataProducerCfg
    // Configuration for FakeDataProducerDAQMOdule
    inline void to_json(json& j, const FakeDataProducerCfg& obj) {
        j["output"] = obj.output;
        j["starting_int"] = obj.starting_int;
        j["ending_int"] = obj.ending_int;
        j["queue_timeout_ms"] = obj.queue_timeout_ms;
        j["wait_between_sends_ms"] = obj.wait_between_sends_ms;
        j["nIntsPerVector"] = obj.nIntsPerVector;
    }
    inline void from_json(const json& j, FakeDataProducerCfg& obj) {
        if (j.contains("output")) {
            j.at("output").get_to(obj.output);
        }
        if (j.contains("starting_int")) {
            j.at("starting_int").get_to(obj.starting_int);
        }
        if (j.contains("ending_int")) {
            j.at("ending_int").get_to(obj.ending_int);
        }
        if (j.contains("queue_timeout_ms")) {
            j.at("queue_timeout_ms").get_to(obj.queue_timeout_ms);
        }
        if (j.contains("wait_between_sends_ms")) {
            j.at("wait_between_sends_ms").get_to(obj.wait_between_sends_ms);
        }
        if (j.contains("nIntsPerVector")) {
            j.at("nIntsPerVector").get_to(obj.nIntsPerVector);
        }
    }
    // Converters for FakeDataConsumerCfg
    // Configuration for FakeDataConsumerDAQMOdule
    inline void to_json(json& j, const FakeDataConsumerCfg& obj) {
        j["input"] = obj.input;
        j["starting_int"] = obj.starting_int;
        j["ending_int"] = obj.ending_int;
        j["queue_timeout_ms"] = obj.queue_timeout_ms;
    }
    inline void from_json(const json& j, FakeDataConsumerCfg& obj) {
        if (j.contains("input")) {
            j.at("input").get_to(obj.input);
        }
        if (j.contains("starting_int")) {
            j.at("starting_int").get_to(obj.starting_int);
        }
        if (j.contains("ending_int")) {
            j.at("ending_int").get_to(obj.ending_int);
        }
        if (j.contains("queue_timeout_ms")) {
            j.at("queue_timeout_ms").get_to(obj.queue_timeout_ms);
        }
    }


} // namespace dunedaq::appfwk

#endif // DUNEDAQ__APPFWK_TEST_NLJS_HPP