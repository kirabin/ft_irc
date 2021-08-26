#include "Command.hpp"

Command::Command() : _name(""), _description(""), _server(NULL), _sender(NULL) {}

Command::~Command() {}

string Command::getName() const {
	return _name;
}

string Command::getDescription() const {
	return _description;
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
