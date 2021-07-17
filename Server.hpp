#ifndef SERVER_HPP
# define SERVER_HPP
# include "main.hpp"
# include "RequestParser.hpp"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstdio>
#include "structure.h"
#include <string>
#include <map>
#define MAX_CLIENTS 20
#include <fcntl.h>
#include "Socket.hpp"
#include "Connection.hpp"
#include "Response.hpp"


class Config;
class Socket;
class Connection;


class Server
{
private:
	int conNumber;
	int							_clientsCount;
	Socket						*_listenSock;
	t_config					*_config;
	struct pollfd				_fd_array[1 /* listen */ + MAX_CLIENTS];
	std::map<int, Connection *>	_mapConnections; //key = fd, value = Connection этого fd


	/********* Private methods *******/
	void	_createListenSocket();
	int		_pollLoop();
	void	_initPollfdStruct();
	void	_copyPollfdStruct(struct pollfd *array);
	void	_addSocketToConnections(Socket *newConnect);
	void	_addToPollfd(int new_fd);
	void	_addToMap(Socket *newSocket);
	void	_checkNewConnection(int &ret);
	void	_removeConnection(Connection *conn, int i);
	void	_clearMap();



public:
	Server();
	Server(const Server &copy);
	~Server();

	Server &operator=(const Server &copy);
	int startServer(struct s_config *config);

	int request(Connection &conn, int i);

	int	responseSend(Connection &conn);




};

#endif
