#ifndef WEBSERV_TEAM_STRUCTURE_H
# define WEBSERV_TEAM_STRUCTURE_H

# include <string>
# include <vector>


/*******************************************
************STANDART CONFIGURATION**********
********************************************
**	server 						: сервер
**		listen 					: порт
**		server_name localhost	: адрес
**		error_page /www/default	: путь к дикектории с ошибками
**		location / 				: путь относительно корня (root)/
**			index index.html	: индекс
**			autoindex off		: автоиндекс
**			methods GET			: метод
**			root 				: путь к корню
**			cgi_alias			: путь к директории со скриптами
*/

typedef struct 	s_location
{
	std::string location;
	std::string index;
	std::string autoindex;
	std::vector<std::string> methods;
	std::string root;
}				t_location;

typedef struct 	s_config
{
	int serverID;
	std::string listen;
	std::string server_name;
	std::string max_body_size;
	std::string error_page;
	std::vector<std::string> cgi_alias;
	std::vector<t_location> location;
}				t_config;



#endif
