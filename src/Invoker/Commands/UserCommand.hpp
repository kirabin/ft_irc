#ifndef UserCommand_hpp
# define UserCommand_hpp
# include "../Command.hpp"

using namespace std;

class UserCommand: public Command {
	public:
		UserCommand();
		virtual ~UserCommand();
		void execute();
};

#endif
