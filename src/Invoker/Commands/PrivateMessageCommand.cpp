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
        Channel* tmp_channel =  this->getChannelFromArg();
        std::string tmp;
        tmp = this->makeString();
        std::cout << tmp << std::endl;
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
    for (size_t i  = 1; i <= _args.size(); i++)
    {
        if (!this->_args[i].empty())
        {

            if (tmp.empty())
            {
                tmp =  this->_args[i];
            }
            else
            {
                tmp = tmp +  " " + this->_args[i];
            }

        }

    }
    tmp.erase(tmp.find_last_not_of(MSG_DELIMITER) + 1);
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
        string getName = _args[0].substr(1, _args[0].size());

        Channel* channel = _server->getChannel(getName);

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
