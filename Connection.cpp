#include "Connection.hpp"

Connection::Connection():

		         _request(),_response(), _state(READING),  _sock_fd(-1), _isOK(0), _sock(NULL), _config(NULL)
{
}

Connection::Connection(Socket *sock, t_config *config):

	    _request(),_response(),_state(READING),_sock_fd(sock->getFd()),  _isOK(0), _sock(sock), _config(config)
{
}

Connection::~Connection()
{
	delete _sock;
}

Connection::Connection(const Connection &copy)
{
	*this = copy;
}

Connection	&Connection::operator=(const Connection &copy)
{
	_request = copy._request;
	_response = copy._response;
	_state = copy._state;
	_sock_fd  = copy._sock_fd;
	_isOK = copy._isOK;
	_sock = copy._sock;
	_config = copy._config;
	return (*this);
}

void Connection::bufHandler(char *buf, int	len)
{
	_isOK = _request.RequestWaiter(buf, len);
}

std::string Connection::responsePrepare()
{

	Response response(_request, _config);

	if (_isOK == 1)
	    _response = response.responseInit();

	return _response;
}




int Connection::get_isOk()
{
	return _isOK;
}


int Connection::getState() const
{
	return _state;
}

void Connection::setState(int state)
{
	_state = state;
}

int Connection::getSockFd() const
{
	return _sock_fd;
}

const std::string &Connection::getResponse() const
{
	return _response;
}

void Connection::setResponse(const std::string &response)
{
	_response = response;
}
