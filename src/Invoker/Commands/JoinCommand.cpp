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
	if (channel) {
		_sender->setChannel(channel);
		channel->sendMessageToChannel(_sender, "joined a channel");
		_sender->getReply(":You joined a channel");
		channel->addUser(_sender);
	} else {
		Channel	*newChannel = _server->createChannel(_args[0], _sender);

		_sender->setChannel(newChannel);
		_sender->getReply(":You created a channel");
		newChannel->addUser(_sender);
	}

}
