#include "HelpCommand.hpp"

HelpCommand::HelpCommand(string name) : Command(name) {}

HelpCommand::~HelpCommand() {}

void HelpCommand::execute(Server* server, User* user, deque<string> args) {
	Command::execute(server, user, args);
}
