#ifndef IRCSERV_HPP
# define IRCSERV_HPP

// include.cpp 
# include <iostream>
# include <sstream>
# include <iomanip>
# include <string>
# include <stdexcept>
# include <vector>

// include.c
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <poll.h>

// class.hpp
// #include "Server.Class.hpp"

# define ENDL		"\r\n"
# define SPC		" * "
# define CMD_SIZE	6
# define SEND_OPT	0

// ----==== Command description ====---- //

# define HELP		"/help"
# define NICK		"/nick"
# define JOIN		"/join"
# define LEAVE		"/leave"
# define WHO		"/who"
# define KICK		"/kick"
# define PASS		"/pass"
# define USER		"/user"

# define HELP_DIS		"/help <> - show a list of available commands"
# define NICK_DIS		"/nick <nick> - сhange your nickname"
# define JOIN_DIS		"/join <#channel> - join or create a channel"
# define LEAVE_DIS		"/leave <#channel> - leave channel"
# define WHO_DIS		"/who <#channel> - show the list of users on channel"
# define KICK_DIS		"/kick <user> <#channel> - kick a user from channel"
# define PASS_DIS		"/pass <passwordtoserver> - kick a user from channel"
# define USER_DIS		"/user <username> <hostname> <servername> <realname> - used at the beginning of connection to specify you on server"

# define WELCOME_MSG(servname)	("Welcome to our server (" + servname + "), Dude!\nBefore you start, you have to do a simple authorization in a few steps:\n\n1) /pass\n2) /username\n3) /nickname\n\nTo learn more about the commands, use /help\n\r\n")
# define LEAVE_SERVER	" leave server"


# define COUT(smth)		(std::cout <<  smth  << std::endl)

// ----==== Command macro ====---- //

// ANY COMMAND
# define ERR_TOOMANYPARAMS(nick, cmd)			("42 * " + nick + "  " + cmd + ": Too many parameters")			// -
# define ERR_NEEDMOREPARAMS(nick, cmd)			("461 * " + nick + "  " + cmd + ": Not enough parameters")		// - Returned when you try use any commands with not enough parameters

// PASS
# define ERR_PASSWDMISMATCH(nick, cmd)			("464 * " + nick + "  " + cmd + ": Password incorrect") 

// NICK
// # define ERR_NONICKNAMEGIVEN(nick, cmd)		("431 * " + nick + "  " + cmd + ": No nickname given")				// - Returned when a nickname parameter expected for a command and isn't found.
// # define ERR_ERRONEUSNICKNAME(nick, cmd)		("432 * " + nick + "  " + cmd + ": Erroneous nickname")				// - Returned after receiving a NICK + message which contains characters which do not fall in the defined set.  See section 2.3.1 for details on valid nicknames
# define ERR_NICKNAMEINUSE(nick, cmd)			("433 * " + nick + "  " + cmd + ": Nickname is already in use")		// - Returned when a NICK + message is processed that results in an attempt to change to a currently existing nickname.

// JOIN
// ERR_NEEDMOREPARAMS
# define ERR_TOOMANYCHANNELS(nick, cmd, chan)	("405 * " + nick + "  " + cmd + " " + chan + ": You have joined too many channels")	// - Returned when you connect to more then one channel
# define ERR_BANNEDFROMCHAN(nick, cmd, chan)	("474 * " + nick + "  " + cmd + " " + chan + ": Cannot join channel (+b)")	// - Returned when you was kicked from channel
# define ERR_BADCHANMASK(nick, cmd, chan)		("476 * " + nick + "  " + cmd + " " + chan + ": No such channel")		// - Returned when you try connect to channel which starts no from #,& 

// KICK
// ERR_NEEDMOREPARAMS
// ERR_NOSUCHCHANNEL
// ERR_BADCHANMASK
// # define ERR_NOTONCHANNEL(nick, cmd, chan)		("442 * " + nick + "  " + cmd + " " + chan + " You're not on that channel") // - USER not on this channel

// LEAVE
// ERR_NEEDMOREPARAMS
// ERR_BADCHANMASK
# define ERR_NOTONCHANNEL(nick, cmd, chan)		("442 * " + nick + "  " + cmd + " " + chan + ": You're not on that channel")	// - Returned when you not on channel
# define ERR_NOSUCHCHANNEL(nick, cmd, chan)		("403 * " + nick + "  " + cmd + " " + chan + ": No such channel")		// - Returned when you try LEAVE not your channel

// WHO
# define RPL_ENDOFWHO(nick, cmd, chan)			("315 * " + nick + " " + cmd + " " + chan + ": End of /WHO list")

// ----==== Log info ====---- //


#endif