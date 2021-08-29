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

	std::string tmp;

	for (size_t i  = 0; i <= _args.size(); i++)
	{
		tmp = tmp +  " " + this->_args[i] ;
	}
	tmp.erase(tmp.find_last_not_of("\n\r") + 1);
	std::cout << "|" << tmp << "|" <<  std::endl;

}
