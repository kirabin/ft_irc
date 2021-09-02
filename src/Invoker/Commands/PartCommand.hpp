#ifndef PartCommand_hpp
# define PartCommand_hpp
# include "../Command.hpp"

using namespace std;

class PartCommand: public Command {
	public:
		PartCommand();
		virtual ~PartCommand();
		void execute();
		void sendReplyToChannel(Channel* channel, string message) const;
};

#endif
