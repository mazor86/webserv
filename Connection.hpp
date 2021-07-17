#ifndef CONNECTION_HPP
# define CONNECTION_HPP
# include <iostream>
# include <map>
# include "RequestParser.hpp"
# include "Socket.hpp"
# include "Response.hpp"
# include "structure.h"

class Socket;
class Response;
class Connection
{
public:
	Connection();
	Connection(Socket *sock, t_config *_config);

	Connection(const Connection &copy);

	~Connection();
	Connection &operator=(const Connection &copy);

	int getState() const;

	int getSockFd() const;

	void setState(int state);

	const std::string &getResponse() const;

	void setResponse(const std::string &response);

	void	bufHandler(char *buf, int	len); 	// эта функция принимает char *buf и длину buf, считанного в данной итерации

	std::string	responsePrepare();

	int get_isOk();

private:
	RequestParser		_request;
	std::string			_response;
	int					_state;
	int					_sock_fd;
	int 				_isOK;
	Socket				*_sock;
	struct s_config		*_config;
};

#endif
