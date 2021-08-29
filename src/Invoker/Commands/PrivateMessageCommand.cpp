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

    if (this->getUserFromArg() != nullptr)
    {
        std::string tmp;
        tmp = _sender->getName() + ": " + this->makeString();
        setSender(this->getUserFromArg());
        _sender->getReply(tmp);
    }
    else if (this->getChannelFromArg() != nullptr)
    {
        std::cout << "channel test" << std::endl;
        Channel* tmp_channel =  this->getChannelFromArg();
        std::cout << "channel test2" << std::endl;
        std::string tmp;
        tmp = _sender->getName() + ": " + this->makeString();
        //TODO не получает канал разобраться почему !!!

        if (tmp_channel && !tmp.empty())
        {
            tmp_channel->sendMessageToChannel(_sender, tmp);
        }
    }
    else
    {
        _sender->getReply("error nick or channel not found");
    }
}
