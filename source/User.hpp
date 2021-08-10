#ifndef User_hpp
# define User_hpp
# include <string>
# include "Channel.hpp"
# define STATUS_REGULAR 0
# define STATUS_OPERATOR 1
using namespace std;


class User {

	protected:
		string _nickname;
		int _status;

	public:
		User(string nickname);

		void joinChannel(Channel channel);
		void sendPrivateMessage(User to);
		void setNickname(string new_nickname);
		string& getNickname() const;

		// Operator functions
		// +o -o
		void setStatus(User user, int status);
};

#endif
