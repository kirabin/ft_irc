#ifndef LeaveCommand_hpp
# define LeaveCommand_hpp
# include "../Command.hpp"

using namespace std;

class LeaveCommand: public Command {
	public:
		LeaveCommand();
		virtual ~LeaveCommand();
		void execute();
};

#endif
