
#ifndef CONFIG_HPP
# define CONFIG_HPP
# include "main.hpp"
# include "Server.hpp"
# include "structure.h"
# define DEFAULT_CONFIG_PATH "config/default.conf"
# include "structure.h"

class Server;


/*
**	струкрура конфигурационного файла описана в "structure.h"
*/

class Config
{
	private:
		std::string _path;
		bool _isValid; 
		int _numOfServers;
		std::vector<t_config> _configs;
		std::vector<Server> _servers;


	public:
		/* constructors, destructor */
		Config();								//записываем в _path дефолтный конфиг
		Config(std::string const &path);		//записываем в _path конфиг который передали
		Config(const Config &copy);
		~Config();
		Config &operator=(const Config &copy);

		/* setters, getters */
		void setPath(const std::string &path);
		std::string getPath();
		std::vector<t_config> getConfigs();
		bool isValid(); //возвращаем bool - is valid or no

		/* config parser/handler */
		void load(std::string path);
		void read(std::vector<std::string> &data);
		void showConfig();


		/*  congig handler */
		void createServers();
};



//enter для продолжения
template<typename M> 
void enter(M message)
{
	int i = -1;
	std::cout << std::setw(30) << std::endl << message << std::endl;
	while (1)
	{
		char str = std::cin.get();
		if (str == 0x0A)
			break ;
		++i;
	}
}


// инициация потока с сервером
template<class STRUCTURE, class SERVER>
void* initServer(void* structure)
{
	STRUCTURE* config = (STRUCTURE*) structure;
	SERVER newServer;
	newServer.startServer(config);
    return 0;
}

// командная строка во время выполнения серверов
template<class Config>
void *cmds(void* object)
{
	Config* obj = (Config*)object;
	std::string cmd;
	(void)obj;

	while(1)
	{
		std::cin >> cmd;
		if (cmd == "exit")
		{
			std::cout << "\e[0;36m" << "Bye" << "\033[0m" << std::endl;
			sleep(1);
			exit(0);
		}
		std::cout << "\e[0;36m" << "webserv: command is not valid" << "\033[0m" <<std::endl;
		
	}
}



#endif





















































// https://demin.ws/blog/russian/2009/02/08/reading-file-via-stl-iterators/
// https://server.179.ru/tasks/cpp/total/161.html

// https://www.8host.com/blog/algoritmy-vybora-blokov-server-i-location-v-nginx/

// https://community.vscale.io/hc/ru/community/posts/209008505-%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0-%D0%B8-%D0%BF%D0%B5%D1%80%D0%B2%D0%B8%D1%87%D0%BD%D0%B0%D1%8F-%D0%BD%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B0-Nginx

// internet-technologies.ru/articles/reshenie-problem-svyazannyh-s-oshibkoy-nginx-403-forbidden.html