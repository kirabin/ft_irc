#include "NickCommand.hpp"

// TODO: Numeric replies
// ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
// ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
// ERR_UNAVAILRESOURCE             ERR_RESTRICTED

// ERR_NEEDMOREPARAMS

NickCommand::NickCommand() {
	_name = "NICK";
	_description = "NICK <nick> - сhange your nickname";
}

NickCommand::~NickCommand() {}

void NickCommand::execute() {

	if (!_sender->isAuthorized())
		throw "You're not authorized, use PASS";

	string oldNick = _sender->getNick();
	if (_args.size() == 0) {
		_sender->getReply("Your nick is @" + oldNick);
		_sender->getReply("");
		return ;
	}

	if (_args.size() != 1)
		throw "Arguments count error";

	string newNick = _args[0];

	if (newNick == oldNick)
		throw "Nick can't be the same as before";
	if (_server->getUser(newNick))
		throw "This nick is already in use";

	_sender->setName(newNick);
	_sender->getReply("Your nick changed to @" + newNick);
	if (_sender->getChannel()) {
		_sender->sendMessageToChannel("@" + oldNick+ "set his nick to " + "@" + newNick);
	}
	_sender->getReply("");
}
