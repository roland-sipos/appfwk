
#ifndef DUNEDAQ__APPFWK__TEST_TEST_STRUCTS_HPP
#define DUNEDAQ__APPFWK__TEST_TEST_STRUCTS_HPP


#include <string>

namespace dunedaq::appfwk::test {


    /// @brief Configuration for FakeDataProducerDAQMOdule
    struct FakeDataProducerCfg {
        std::string output;
        int nIntsPerVector_;
        int starting_int;
        int ending_int;
        int queue_timeout_ms;
        int wait_between_sends_ms;
    };


    /// @brief Configuration for FakeDataConsumerDAQMOdule
    struct FakeDataConsumerCfg {
        std::string input;
        int nIntsPerVector_;
        int starting_int;
        int ending_int;
        int queue_timeout_ms;
    };


} // namespace dunedaq::appfwk::test

#endif // DUNEDAQ__APPFWK__TEST_TEST_STRUCTS_HPP