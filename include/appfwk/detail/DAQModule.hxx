namespace dunedaq::appfwk {

template<typename Child>
void
<<<<<<< HEAD
DAQModule::register_command(const std::string& name, void (Child::*f)(data_t))
=======
DAQModule::register_command(const std::string& name, void (Child::*f)(const data_t&))
>>>>>>> 29dc0fb2a58beebbc254ce5688a54dbe22384f3e
{
  using namespace std::placeholders;

  bool done = commands_.emplace(name, std::bind(f, dynamic_cast<Child*>(this), _1)).second;
  if (!done) {
    // Throw here
    throw CommandRegistrationFailed(ERS_HERE, get_name(), name);
  }
}

} // namespace dunedaq::appfwk
