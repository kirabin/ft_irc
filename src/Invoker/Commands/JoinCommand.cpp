#include "JoinCommand.hpp"

JoinCommand::JoinCommand() {
	 _name = "JOIN";
	 _description = "JOIN <#channel> - join or create a channel";
}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute() {

	if (!_sender->didRegister())
		throw ERR_RESTRICTED;
	if (_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(_name);
	if (_sender->getChannel() != nullptr)
		throw ERR_TOOMANYCHANNELS(_sender->getChannel()->getName());
	if (!isAllowedChannelName(_args[0]))
		throw ERR_BADCHANMASK(_args[0]);

	Channel *channel = _server->getChannel(_args[0]);
	if (!channel) {
		channel = _server->createChannel(_args[0], _sender);
	}
	_sender->setChannel(channel);
	channel->addUser(_sender);
	sendReplyToChannel(channel, _sender->getPrefix() + " " + this->_name + " #" + channel->getName());
}

void JoinCommand::sendReplyToChannel(Channel* channel, string message) const {
	vector<User *>::iterator	user;
	vector<User *>				users = channel->getUsers();

	for (user = users.begin(); user != users.end(); user++) {
		(*user)->getReply(message);
	}
}
