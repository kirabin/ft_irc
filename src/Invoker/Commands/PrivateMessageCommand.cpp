#include "PrivateMessageCommand.hpp"

//  Numeric Replies:

//    ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
//    ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
//    ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
//    ERR_NOSUCHNICK
//    RPL_AWAY

PrivateMessageCommand::PrivateMessageCommand() {
	_name = "PRIVMSG";
	_description = "";
}

PrivateMessageCommand::~PrivateMessageCommand() {}

void PrivateMessageCommand::execute() {
	if (!_sender->didRegister())
		throw ERR_RESTRICTED;

    if (this->getSender() != nullptr)
    {
        std::string tmp;
        tmp = _sender->getName() + ": " + this->makeString();
        setSender(this->getSender());
        _sender->getReply(tmp);
    }
    else if ( _server->getChannel(_args[0]) != nullptr)
    {
        Channel* tmp_channel =   _server->getChannel(_args[0]);
        std::string tmp;
        tmp = _sender->getName() + ": " + this->makeString();
        tmp_channel->sendMessageToChannel(_sender, tmp);
    }
    else
    {
        _sender->getReply("error nick or channel not found");
    }
}
