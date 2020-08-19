/**
 * @file FakeDataProducerDAQModule.cc FakeDataProducerDAQModule class
 * implementation
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "TestNljs.hpp"
#include "FakeDataProducerDAQModule.hpp"
#include "appfwk/CmdStructs.hpp"
#include <chrono>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <TRACE/trace.h>
/**
 * @brief Name used by TRACE TLOG calls from this source file
 */
#define TRACE_NAME "FakeDataProducer" // NOLINT

namespace dunedaq {
namespace appfwk {

FakeDataProducerDAQModule::FakeDataProducerDAQModule(const std::string& name)
  : DAQModule(name)
  , thread_(std::bind(&FakeDataProducerDAQModule::do_work, this, std::placeholders::_1))
  , outputQueue_(nullptr)
  , queueTimeout_(100)
{
  register_command(cmd::IdNames::conf, &FakeDataProducerDAQModule::do_configure);
  register_command(cmd::IdNames::scrap, &FakeDataProducerDAQModule::do_unconfigure);
  register_command(cmd::IdNames::start, &FakeDataProducerDAQModule::do_start);
  register_command(cmd::IdNames::stop, &FakeDataProducerDAQModule::do_stop);
}

void
FakeDataProducerDAQModule::do_configure(data_t obj)
{
  cfg_ = obj.get<FakeDataProducerCfg>();
  outputQueue_.reset(new DAQSink<std::vector<int>>(cfg_.output));
  queueTimeout_ = std::chrono::milliseconds(cfg_.queue_timeout_ms);
}
void
FakeDataProducerDAQModule::do_unconfigure(data_t)
{
  outputQueue_.reset();
  queueTimeout_ = std::chrono::milliseconds(100);
}

void
FakeDataProducerDAQModule::do_start(data_t /*args*/)
{
  thread_.start_working_thread();
}

void
FakeDataProducerDAQModule::do_stop(data_t /*args*/)
{
  thread_.stop_working_thread();
}

/**
 * @brief Format a std::vector<int> to a stream
 * @param t ostream Instance
 * @param ints Vector to format
 * @return ostream Instance
 */
std::ostream&
operator<<(std::ostream& t, std::vector<int> ints)
{
  t << "{";
  bool first = true;
  for (auto& i : ints) {
    if (!first)
      t << ", ";
    first = false;
    t << i;
  }
  return t << "}";
}

void
FakeDataProducerDAQModule::do_work(std::atomic<bool>& running_flag)
{
  int current_int = cfg_.starting_int;
  size_t counter = 0;
  std::ostringstream oss;

  while (running_flag.load()) {
    TLOG(TLVL_TRACE) << get_name() << ": Creating output vector";
    std::vector<int> output(cfg_.nIntsPerVector);

    TLOG(TLVL_TRACE) << get_name() << ": Start of fill loop";
    for (size_t ii = 0; ii < cfg_.nIntsPerVector; ++ii) {
      output[ii] = current_int;
      ++current_int;
      if (current_int > cfg_.ending_int)
        current_int = cfg_.starting_int;
    }
    oss << "Produced vector " << counter << " with contents " << output << " and size " << output.size();
    ers::debug(ProducerProgressUpdate(ERS_HERE, get_name(), oss.str()));
    oss.str("");

    TLOG(TLVL_TRACE) << get_name() << ": Pushing vector into outputQueue";
    try {
      outputQueue_->push(std::move(output), queueTimeout_);
    } catch(const QueueTimeoutExpired& ex) {
      ers::warning(ex);
    }

    TLOG(TLVL_TRACE) << get_name() << ": Start of sleep between sends";
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg_.wait_between_sends_ms));
    TLOG(TLVL_TRACE) << get_name() << ": End of do_work loop";
    counter++;
  }
}

} // namespace appfwk
} // namespace dunedaq

DEFINE_DUNE_DAQ_MODULE(dunedaq::appfwk::FakeDataProducerDAQModule)

// Local Variables:
// c-basic-offset: 2
// End:
