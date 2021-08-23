#include "WhoCommand.hpp"

WhoCommand::WhoCommand() {
	_name = "/who";
	_description = "/who <#channel> - show the list of users on channel";
}

WhoCommand::~WhoCommand() {}

void WhoCommand::execute() {

	if (!_sender->isAuthorized())
		throw "You're not authorized, use /pass";
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
