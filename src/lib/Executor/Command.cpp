#include "Command.hpp"

Command::Command(string name) : _name(name) {}
Command::~Command() {}

void Command::execute() {
	cout << "Executing " << _name << endl;
}

string Command::getName() {
	return _name;
}

HelpCommand::HelpCommand(string name) : Command(name) {}
HelpCommand::~HelpCommand() {}
void HelpCommand::execute() {
	Command::execute();
}

NickCommand::NickCommand(string name) : Command(name) {}
NickCommand::~NickCommand() {}
void NickCommand::execute() {
	Command::execute();
}

JoinCommand::JoinCommand(string name) : Command(name) {}
JoinCommand::~JoinCommand() {}
void JoinCommand::execute() {
	Command::execute();
}

LeaveCommand::LeaveCommand(string name) : Command(name) {}
LeaveCommand::~LeaveCommand() {}
void LeaveCommand::execute() {
	Command::execute();

}

WhoCommand::WhoCommand(string name) : Command(name) {}
WhoCommand::~WhoCommand() {}
void WhoCommand::execute() {
	Command::execute();
}

KickCommand::KickCommand(string name) : Command(name) {}
KickCommand::~KickCommand() {}
void KickCommand::execute() {
	Command::execute();
}
