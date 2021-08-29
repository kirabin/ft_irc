#include "WhoCommand.hpp"

WhoCommand::WhoCommand() {
	_name = "WHO";
	_description = "WHO <#channel> - show the list of users on channel";
}

WhoCommand::~WhoCommand() {}

void WhoCommand::execute() {

	if (!_sender->isAuthorized())
		throw ERR_RESTRICTED;
	if (_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(_name);

	Channel *channel = _server->getChannel(_args[0]);
	if (channel == nullptr)
		throw ERR_NOSUCHCHANNEL(_args[0]);

	vector<User*> users = channel->getUsers();
	_sender->getReply("Channel " + channel->getName() + " has " + std::to_string(users.size()) + " users");

	vector<User*>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		if (channel->getAdmin() == *it)
			_sender->getReply("@" + (*it)->getName());
		else
			_sender->getReply((*it)->getName());
	}

}
