#ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP

class Channel;

# include "../Utils/ircserv.hpp"
# include "../User/User.hpp"

# define SEND_OPT	0

class Channel
{
	private:
		std::string			_name;
		std::vector<User *>	_users;
		User*				_admin;


		Channel();

	public:
		Channel(std::string name, User* admin);
		~Channel();

		std::string		getName()const;
		User			*getAdmin()const;

		void			addUser(User *newUser);
		void			removeUser(User *user);

		void			sendMessageToUser(User* user, std::string message);
		void			sendMessageToChannel(User *sender, std::string message);
		void			sendServiceMessageToChannel(std::string message);

		void			printShortInfo()const;
		void			printFullInfo()const;

		bool			isUser(User *user)const;
};

#endif
