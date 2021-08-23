#include "KickCommand.hpp"

KickCommand::KickCommand() {
	_name = "/kick";
	_description = "/kick <user> <#channel> - kick a user from channel";
}

KickCommand::~KickCommand() {}

void KickCommand::execute() {

	if (!_sender->isAuthorized())
		throw "You're not authorized, use /pass";
	if (_args.size() != 2)
		throw "Arguments count error";

	Channel	*channel = _server->getChannel(_args[1]);

	if (channel->getAdmin() != _sender)
		throw "You're not an admin of this channel";
	if (channel == nullptr)
		throw "No such channel";

	User *userToKick = channel->getUser(_args[0]);

	if (userToKick == nullptr)
		throw "No such user on this channel";
	if (userToKick == _sender)
		throw "Can't kick oneself";

	channel->sendMessageToChannel(_sender, "kicked" + userToKick->getName());
	channel->removeUser(userToKick);
	_sender->getReply("");
}
