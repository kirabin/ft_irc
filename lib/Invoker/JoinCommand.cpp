#include "JoinCommand.hpp"

JoinCommand::JoinCommand() {
	 _name = "/join";
	 _description = "/join <#channel> - join or create a channel";
}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute() {

	if (!_sender->isAuthorized())
		throw "You're not authorized, use /pass";
	if (_args.size() != 1)
		throw "Arguments count error";
	if (_sender->getChannel() != nullptr)
		throw "You already joined a channel";
	if (_args[0].size() < 2 || _args[0][0] != '#')
		throw "Bad channel name";

	Channel *channel = _server->getChannel(_args[0]);
	if (channel) {
		_sender->setChannel(channel);
		channel->sendMessageToChannel(_sender, "joined a channel");
		_sender->getReply("You joined a channel");
		channel->addUser(_sender);
	} else {
		Channel	*newChannel = _server->createChannel(_args[0], _sender);

		_sender->setChannel(newChannel);
		_sender->getReply("You created a channel");
		newChannel->addUser(_sender);
	}
	_sender->getReply("");
}
