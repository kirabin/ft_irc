#ifndef USER_CLASS_HPP
# define USER_CLASS_HPP

class User;

# include "../Utils/ircserv.hpp"
# include "../Channel/Channel.hpp"

using std::vector;
using std::string;

class User
{
	private:
		string				_id;
		bool				_didEnter;
		bool				_didRegister;
		int					_sockFd;
		int					_port;
		string				_host;
		string				_nick;
		string				_username;
		string				_realname;
		string				_message;

		// TODO: user should be able to join multiple channels
		static size_t		_maxChannels;
		vector<Channel *>	_channels;
		Channel*			_channel;

	public:

		User(int sockFd, int port);
		User(int sockFd, char *host, int port);
		~User();

		bool			didEnter() const;
		void			setDidEnter(bool value);
		bool			didRegister() const;
		void			doRegister();
		int				getSockFd() const;
		int				getPort() const;
		string		getNick() const;
		string		getHost() const;
		string		getMessage() const;
		string		getSign() const;
		Channel			*getChannel() const;
		string		getName() const;
		void			setNick(string nickname);
		void			setUsername(string username);
		void			setRealname(string realname);


		void			setAuthorized(bool enter);
		void			setChannel(Channel *channel);
		string			getId() const;
		void			removeUserFromChannel();
		void			appendMessage(string message);
		void			clearMessage();
		void			sendMessageToChannel(string message);
		void			getReply(string message);
		void			printShortInfo()const;
		string			get_id();
};

#endif
