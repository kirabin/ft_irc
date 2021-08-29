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
    User* test = _server->getUser(_args[0]);
	std::cout << "this is get comman: |" << this->makeString() << "|" <<  std::endl;
    setSender(test);
    _sender->getReply(this->makeString());
}
