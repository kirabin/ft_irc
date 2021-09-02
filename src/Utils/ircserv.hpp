#ifndef IRCSERV_HPP
# define IRCSERV_HPP

# include <iostream>
# include <sstream>
# include <iomanip>
# include <string>
# include <stdexcept>
# include <vector>

# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include <unistd.h>
# include <poll.h>

# define MSG_DELIMITER "\r\n"

// REPLIES
#define RPL_WELCOME(nick, username, host)		"001 * Welcome to the Internet Relay Network " +  nick + "!" + username + "@" + host
#define RPL_LIST(channel, usersCount)			("322 * #" + channel + " " + usersCount)
#define RPL_LISTEND								"323 * :End of LIST"



// ERRORS
# define ERR_NEEDMOREPARAMS(command)			("461 * " + command + ": Not enough parameters")
# define ERR_ALREADYREGISTRED					"462 * :Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH						"464 * :Password incorrect"
# define ERR_NICKNAMEINUSE(nick)				("433 * " + nick + ":Nickname is already in use")
# define ERR_RESTRICTED							"484 * :Your connection is restricted!"
# define ERR_NOTONCHANNEL(channel)				("442 * " + channel + ":You're not on that channel")
# define ERR_NOSUCHCHANNEL(channel)				("403 * #" + channel + ":No such channel")
# define ERR_CHANOPRIVSNEEDED(channel)			("482 * #" + channel + ":You're not channel operator")
# define ERR_USERNOTINCHANNEL(nick, channel)	("441 * " + nick + " #" + channel + ":They aren't on that channel")
# define ERR_BADCHANMASK(channel)				("476 * #" + channel + ":Bad Channel Mask")

// TODO: ERR_TOOMANYCHANNELS should have max number of allowed channels
# define ERR_TOOMANYCHANNELS(channel)			("405 * #" + channel + ":You have joined too many channels")

#endif
