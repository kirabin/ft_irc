#include "PartCommand.hpp"

PartCommand::PartCommand() {
	_name = "PART";
	_description = "PART #channel - leave channel";
}

PartCommand::~PartCommand() {}

void PartCommand::execute() {

	if (!_sender->didRegister())
		throw ERR_RESTRICTED;
	if (_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(_name);

	Channel *channel = _server->getChannel(_args[0]);
	if (!channel)
		throw ERR_NOSUCHCHANNEL(_args[0]);
	if (_sender->getChannel() != channel)
		throw ERR_NOTONCHANNEL(_args[0]);

	sendReplyToChannel(channel, _sender->getPrefix() + " " + this->_name + " #" + channel->getName());
	_sender->removeUserFromChannel();
	_sender->setChannel(nullptr);
}

void PartCommand::sendReplyToChannel(Channel* channel, string message) const {
	vector<User *>::iterator	user;
	vector<User *>				users = channel->getUsers();

	for (user = users.begin(); user != users.end(); user++) {
		(*user)->getReply(message);
	}
}
