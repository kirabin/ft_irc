#include "Command.hpp"

Command::Command(string name) : _name(name), _server(NULL), _sender(NULL) {}

Command::~Command() {}

string Command::getName() const {
	return _name;
}

void Command::setSender(User* sender) {
	_sender = sender;
}

void Command::setServer(Server* server) {
	_server = server;
}

void Command::setArgs(deque<string> args) {
	_args = args;
}
