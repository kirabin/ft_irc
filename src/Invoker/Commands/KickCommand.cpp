#include "KickCommand.hpp"

KickCommand::KickCommand() {
	_name = "KICK";
	_description = "KICK <user> <#channel> - kick a user from channel";
}

KickCommand::~KickCommand() {}

void KickCommand::execute() {

	if (!_sender->isAuthorized())
		throw ERR_RESTRICTED;
	if (_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(_name);
	if (_args[1][0] != '#')
		throw ERR_BADCHANMASK(_args[1]);

	Channel	*channel = _server->getChannel(_args[1]);

	if (channel == nullptr)
		throw ERR_NOSUCHCHANNEL(channel->getName());
	if (!channel->getUser(_sender->getNick()))
		throw ERR_NOTONCHANNEL(channel->getName());
	if (channel->getAdmin() != _sender)
		throw ERR_CHANOPRIVSNEEDED(channel->getName());

	User *userToKick = channel->getUser(_args[0]);

	if (userToKick == nullptr)
		throw ERR_USERNOTINCHANNEL(_args[0], channel->getName());

	channel->sendMessageToChannel(_sender, "kicked" + userToKick->getName());
	channel->removeUser(userToKick);
	_sender->getReply("");
}
