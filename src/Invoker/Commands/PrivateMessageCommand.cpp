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
	this->clearArg();
}

std::string PrivateMessageCommand::makeString() {

    std::string tmp;
    for (size_t i  = 0; i <= _args.size(); i++)
    {
        if (i == 0 && _server->getUser(_args[i]) == nullptr && _server->getChannel(_args[i]) == nullptr)
        {
            tmp = this->_args[i] ;
        }
        else if ((_server->getUser(_args[i]) != nullptr) || (_server->getChannel(_args[i]) != nullptr))
        {
           ;
        }
        else
        {
            if (tmp.empty())
            {
                tmp =  this->_args[i] ;
            }
           else
            {
                tmp = tmp +  " " + this->_args[i] ;
            }
        }
    }
    tmp.erase(tmp.find_last_not_of("\n\r") + 1);
    return tmp;
}

User *PrivateMessageCommand::getUserFromArg() {
    if (_args.empty())
    {
        return nullptr;
    }
    else
    {
        User* user = _server->getUser(_args[0]);

        if (user == nullptr)
        {
            return  nullptr;
        }
        else
        {
            if(user  != nullptr)
            {
                return  user;
            }
        }
        return nullptr;
    }
}

void PrivateMessageCommand::clearArg() {
    _args.erase(_args.begin(), _args.end());
}

Channel *PrivateMessageCommand::getChannelFromArg() {
    if (_args.empty())
    {
        return nullptr;
    }
    else
    {
        Channel* channel = _server->getChannel(_args[0]);

        if (channel == nullptr)
        {
            return  nullptr;
        }
        else
        {
            if(channel  != nullptr)
            {
                return  channel;
            }
        }
        return nullptr;
    }
}
