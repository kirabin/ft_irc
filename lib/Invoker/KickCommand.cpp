#include "KickCommand.hpp"

KickCommand::KickCommand(string name) : Command(name) {}

KickCommand::~KickCommand() {}

void KickCommand::execute() {

	if (_args.size() != 2)
		throw "Error: Arguments error";
	Channel	*channel = _server->getChannel(_args[1]);

	if (channel->getAdmin() != _sender)
		throw "Error: You're not an admin of this channel";
	if (channel == nullptr)
		throw "Error: No such channel";

	User *userToKick = channel->getUser(_args[0]);

	if (userToKick == nullptr)
		throw "Error: No such user on this channel";
	if (userToKick == _sender)
		throw "Error: Can't kick oneself";

	channel->sendMessageToChannel(_sender, "kicked" + userToKick->getName());
	channel->removeUser(userToKick);
}
