#ifndef QuitCommand_hpp
# define QuitCommand_hpp
# include "../Command.hpp"

// TODO: leave channel then 

using namespace std;

class QuitCommand: public Command {
	public:
		QuitCommand();
		virtual ~QuitCommand();
		void execute();
};

#endif
