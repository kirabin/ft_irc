#include "WhoCommand.hpp"

WhoCommand::WhoCommand(string name) : Command(name) {}

WhoCommand::~WhoCommand() {}

void WhoCommand::execute() {

	if (_args.size() != 1)
		throw "Arguments count error";

	Channel *channel = _server->getChannel(_args[0]);

	if (channel == nullptr)
		throw "No such channel";

	vector<User*> users = channel->getUsers();
	_sender->getReply("Channel " + channel->getName() + " has " + std::to_string(users.size()) + " users");

	vector<User*>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		_sender->getReply("@" + (*it)->getName());
	}
	_sender->getReply("");
}