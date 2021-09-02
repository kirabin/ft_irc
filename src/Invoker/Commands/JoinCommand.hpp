#ifndef JoinCommand_hpp
# define JoinCommand_hpp
# include "../Command.hpp"

using namespace std;

class JoinCommand: public Command {
	public:
		JoinCommand();
		virtual ~JoinCommand();
		void execute();
		void sendReplyToChannel(Channel* channel, string message) const;
};

#endif
