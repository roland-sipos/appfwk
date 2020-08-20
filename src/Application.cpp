#include "appfwk/Application.hpp"

using namespace dunedaq::appfwk;

Application::Application(std::string name) : CommandHandler(name) {}
Application::~Application() { }

