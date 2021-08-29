#ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP

class Channel;

# include "../Utils/ircserv.hpp"
# include "../User/User.hpp"
# include "../Server/Server.hpp"

bool isAllowedChannelName(std::string name);

class Channel
{
	private:
		std::string			_name;
		std::vector<User *>	_users;
		User*				_admin;
		Server*				_server;


		Channel();

	public:
		Channel(std::string name, User* admin, Server *server);
		~Channel();

		std::string		getName() const;
		User			*getAdmin() const;
		User			*getUser(std::string userName);
		std::vector<User *> getUsers() const;

		void			addUser(User *newUser);
		void			removeUser(User *user);

		void			sendMessageToUser(User* user, std::string message);
		void			sendMessageToChannel(User *sender, std::string message);
		void			sendServiceMessageToChannel(std::string message);

		void			printShortInfo()const;
		void			printFullInfo()const;

		bool			isUser(User *user)const;
		void			setName(std::string name);
};

#endif
