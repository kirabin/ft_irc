#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP

class Server;

# include <vector>
# include "../Utils/ircserv.hpp"
# include "../User/User.hpp"
# include "../Channel/Channel.hpp"
# include "../Invoker/Invoker.hpp"

# define MAX_CONNECTION				1000
# define RECV_FLAGS					0
# define SOCKET_CLOSED_BY_CLIENT	"Socket closed by client "


class Server
{
	private:
		int						_sock;
		const std::string		_host;
		const std::string		_port;
		const std::string		_password;
		std::string				_servname;
		std::vector<pollfd>		_pollfds;
		std::vector<User *>		_users;
		std::vector<Channel *>	_channels;
		Invoker					*_Invoker;

		Server();
		int				        createSocket();
		int				        recvMsg(User *user);

	public:
		Server(const std::string host, const std::string port, const std::string password);
		~Server();
        void			        removeUser(std::string id);
        int				        acceptUser();
        User			        *getUser(int sock);
        User			        *getUser(std::string userName);
        User			        *getUserById(std::string id);
        void                    removeUserFromPoll(std::string id);
        void                    removeUserFromUsers(std::string id);
        void                    removeUserFromChannel();
        //getters
        int				        getSock()const;
        std::string		        getPort()const;
        std::string		        getHost()const;
        std::string		        getServname()const;
        //channel
        std::vector<Channel*>   getChannels();
        Channel			        *getChannel(std::string chanName);
        Channel			        *createChannel(std::string name, User *admin);
        //other methods
		void			        start();
		void			        greeting(int client_d)const;
		void			        action();
		void			        log(std::string text);
		bool			        checkPassword(std::string userPassword);

		void                    show_pollfd();
};

#endif
