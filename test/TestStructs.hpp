/*
 * This file is 100% generated.  Any manual edits will likely be lost.
 */
#ifndef DUNEDAQ__APPFWK_TEST_STRUCTS_HPP
#define DUNEDAQ__APPFWK_TEST_STRUCTS_HPP

#include <string>

namespace dunedaq::appfwk {


    /// @brief Configuration for FakeDataProducerDAQMOdule
    struct FakeDataProducerCfg {
        std::string output;
        int32_t starting_int;
        int32_t ending_int;
        int32_t queue_timeout_ms;
        int32_t wait_between_sends_ms;
        uint64_t nIntsPerVector;
    };


    /// @brief Configuration for FakeDataConsumerDAQMOdule
    struct FakeDataConsumerCfg {
        std::string input;
        int32_t starting_int;
        int32_t ending_int;
        int32_t queue_timeout_ms;
    };


} // namespace dunedaq::appfwk

#endif // DUNEDAQ__APPFWK_TEST_STRUCTS_HPP