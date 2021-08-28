#ifndef PrivateMessageCommand_hpp
# define PrivateMessageCommand_hpp
# include "../Command.hpp"

using namespace std;

class PrivateMessageCommand: public Command {
	public:
		PrivateMessageCommand();
		virtual ~PrivateMessageCommand();
		void execute();
};

#endif
