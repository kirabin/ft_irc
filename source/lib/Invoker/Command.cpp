#include "Command.hpp"

Command::Command(string name) : _name(name) {}
Command::~Command() {}

void Command::execute(Server* server, User* user, deque<string> args) {
	cout << "Executing " << _name << endl;
	(void)server;
	(void)user;
	(void)args;
}

string Command::getName() {
	return _name;
}
