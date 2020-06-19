/**
 * @file FakeDataConsumerDAQModule.hpp
 *
 * FakeDataConsumerDAQModule is a simple DAQModule implementation that simply
 * logs the fact that it received a command from DAQProcess.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef APP_FRAMEWORK_TEST_FAKEDATACONSUMERDAQMODULE_HH_
#define APP_FRAMEWORK_TEST_FAKEDATACONSUMERDAQMODULE_HH_

#include "appfwk/DAQModule.hpp"
#include "appfwk/DAQSource.hpp"
#include "appfwk/ThreadHelper.hpp"

#include <ers/Issue.h>

#include <future>
#include <memory>
#include <string>
#include <vector>

namespace dunedaq {
namespace appfwk {
/**
 * @brief FakeDataConsumerDAQModule creates vectors of ints and sends them
 * downstream
 */
class FakeDataConsumerDAQModule : public DAQModule
{
public:
  /**
   * @brief FakeDataConsumerDAQModule Constructor
   * @param name Instance name for this FakeDataConsumerDAQModule instance
   */
  explicit FakeDataConsumerDAQModule(const std::string& name);

  FakeDataConsumerDAQModule(const FakeDataConsumerDAQModule&) =
    delete; ///< FakeDataConsumerDAQModule is not copy-constructible
  FakeDataConsumerDAQModule& operator=(const FakeDataConsumerDAQModule&) =
    delete; ///< FakeDataConsumerDAQModule is not copy-assignable
  FakeDataConsumerDAQModule(FakeDataConsumerDAQModule&&) =
    delete; ///< FakeDataConsumerDAQModule is not move-constructible
  FakeDataConsumerDAQModule& operator=(FakeDataConsumerDAQModule&&) =
    delete; ///< FakeDataConsumerDAQModule is not move-assignable

  void init() override;

private:
  // Commands
  void do_configure(const std::vector<std::string>& args);
  void do_start(const std::vector<std::string>& args);
  void do_stop(const std::vector<std::string>& args);

  // Threading
  void do_work();
  ThreadHelper thread_;

  // Configuration (for validation)
  size_t nIntsPerVector_;
  int starting_int_;
  int ending_int_;
  std::chrono::milliseconds queueTimeout_;
  std::unique_ptr<DAQSource<std::vector<int>>> inputQueue_;
};

} // namespace appfwk
ERS_DECLARE_ISSUE_BASE(appfwk,
                       ConsumerErrorDetected,
                       appfwk::GeneralDAQModuleIssue,
                       name << ": Error in received vector " << counter << " at position " << position << ": Expected "
                            << expected << ", received " << received,
                       ERS_EMPTY,
                       ((std::string)name)((int)counter)((int)position)((int)expected)((int)received))
ERS_DECLARE_ISSUE_BASE(appfwk,
                       ConsumerProgressUpdate,
                       appfwk::GeneralDAQModuleIssue,
                       name << ": " << message,
    ERS_EMPTY,
                       ((std::string)name)((std::string)message))
} // namespace dunedaq

#endif // APP_FRAMEWORK_TEST_FAKEDATACONSUMERDAQMODULE_HH_
