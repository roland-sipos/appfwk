/** @file ddnode.cpp DUNE DAQ Node
 *
 * Usage:
 *
 *     ddnode <command-source> <URI>
 *
 * This program provides a fully generic, command-driven application.
 *
 * Executing a process of this application is fully parameterized by
 * the named command source which produces a sequence of command
 * objects derived from the URI.  Subsequent behavior depends entirely
 * on the content of the produced commands.  Regardless of command
 * source selected, commands are interprted, and thus process behavior
 * determined, in a common way.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "ers/Issue.h"
#include "appfwk/Application.hpp"
#include "appfwk/CommandSource.hpp"

namespace dunedaq {
ERS_DECLARE_ISSUE(appfwk,          // namespace
                  BadUsage, // issue class name
                  "usage: ddnode <sourcetype> <uri>",) // message
}
int main(int argc, char* argv[])
{
    using namespace dunedaq::appfwk;

    if (argc != 3) {
	throw BadUsage(ERS_HERE);
    }
    const std::string csname = argv[1];
    const std::string csuri = argv[2];

    AppFSM app("ddnode");

    auto cs = makeCommandSource(csname, csuri);
    while (true) {
        auto command = cs->recv();
        auto reply = app.handle(command);
        cs->send(reply);
    }
    return 0;    
}
