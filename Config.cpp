
#include "Config.hpp"
# include <pthread.h>

Config::Config():
	_path(std::string(DEFAULT_CONFIG_PATH)), _isValid(true), _numOfServers(0),
	_configs(), _servers()
{
}

Config::Config(std::string const &path):
	_path(path), _isValid(true), _numOfServers(0),
	_configs(), _servers()
{
}

Config::~Config()
{
}

Config::Config(const Config &copy)
{
	*this = copy;
}

Config	&Config::operator=(const Config &copy)
{
	this->_path = copy._path;
	this->_isValid = copy._isValid;
	this->_numOfServers = copy._numOfServers;
	this->_configs = copy._configs;
	this->_servers = copy._servers;
	return (*this);
}

/*-------------------------------------------------------------------------------*/

void Config::setPath(const std::string &path)
{
	_path = path;
}

std::string Config::getPath()
{
	return _path;
}

std::vector<t_config> Config::getConfigs()
{
	return _configs;
}

bool Config::isValid()
{
	return _isValid;
}



/*-------------------------------------------------------------------------------*/



void Config::load(std::string path)
{
	std::vector<std::string> data;
	std::string buffer;
	std::ifstream file;

	file.open(path.c_str());
	if (!(file.is_open()))
	{
		std::cout << YELLOW << "config error: configuraion path is bad\n" << RESET;
		_isValid = false;
		return ;
	}

	/* записываем строки разбитые по пробелу в вектор data */
	while(!file.eof()) 
	{
        file >> buffer;
         data.push_back(buffer);
    }

	file.close();
	read(data);
}




void Config::read(std::vector<std::string> &data)
{
	/* вывод data (не распарсенные данные из конфига) */

	{	/* подсчет серверов в конфиге */
		for(std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++) 
		{
			if (*it == "server")
				_numOfServers += 1;
		}
		if (_numOfServers == 0) //если серверов не найдено, то возвращаем ошибку
		{
			std::cout << YELLOW << "config error: there is no required server to run\n" << RESET;
			_isValid = false;
			return ;
		}
		std::cout << BLUE << "The number of servers will be started: " << GREEN_B << _numOfServers << "\n" << RESET;
	}

	{	/* проверка на четность скобок */
		int openBrace = 0;
		int closeBrace = 0;
		for(std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++) 
		{
			if (*it == "{")
				openBrace += 1;
			if (*it == "}")
				closeBrace += 1;
		}
		if (openBrace != closeBrace) //если скобок не одинаковое количество, то возвращаем ошибку
		{
			std::cout << YELLOW << "config error: wrong number of brackets\n" << RESET;
			_isValid = false;
			return ;
		}
	}


	std::cout << BLUE << "\nMap of configuration file:\n" << RESET;
 
	/* старт парсинга */
	for(int i = 0; i < _numOfServers; i++)
	{
		if (data[0] == "server") 
		{
			std::cout << std::setw(12) << BLUE_B << data[0] << "\n" << RESET;
			t_config new_config;
			new_config.serverID = i;
			std::vector<std::string>::iterator it = data.begin();

			for(unsigned long j = 1; j < data.size(); j++)							//начинаем с единицы чтобы не попасть на "server"
			{
				if (data[j] == "listen")
					new_config.listen = data[j+1];
				if (data[j] == "server_name")
					new_config.server_name = data[j+1];
				if (data[j] == "max_body_size")
					new_config.max_body_size = data[j+1];
				if (data[j] == "error_page")
					new_config.error_page = data[j+1];
				if (data[j] == "cgi_alias")
				{
					for (int c = 1; data[j+c].find("/cgi_bin") != std::string::npos && c < 3; c++)
					{
						new_config.cgi_alias.push_back(data[j + c]);
					}	
				}
				if (data[j] == "location")//////////////
				{
					std::cout << std::setw(15) << BLUE << "location\n" << RESET;
					t_location new_location;
					for(unsigned long l = j; l < data.size(); l++)
					{
						if (data[l] == "location")
							new_location.location = data[l + 1];
						if (data[l] == "index")
							new_location.index = data[l + 1];
						if (data[l] == "autoindex")
							new_location.autoindex = data[l + 1];
						if (data[l] == "methods")
						{
							for (int m = 1; data[l+m] == "GET" || data[l + m] == "POST" || data[l + m] == "DELETE" || data[l + m] == "PUT"; m++)
							{
								new_location.methods.push_back(data[l + m]);
							}	
						}
						if (data[l] == "root")
							new_location.root = data[l + 1];
						if (data[l] == "}")
							break ;
					}
					new_config.location.push_back(new_location);
				}
				if (data[j] == "server")
				{	
					it++;
					data.erase(data.begin(), it);
					break ;
				}
				it++;
			}
			_configs.push_back(new_config);
		} 
		else 
		{
			std::cout << YELLOW << "config error: is not valid\n" << RESET;
			_isValid = false;
			return ;
		}

	}

}



void Config::showConfig()
{
	std::cout << BLUE << "\n\n************************************CONFIG:\n" << RESET;
	for(unsigned long k = 0; k < _configs.size(); k++)
	{	
		std::cout << std::setw(14)<< BLUE_B << "========SERVER[" << k << "]========\n" << RESET;
		std::cout << std::setw(13) << BLUE  << "listen: " << RESET << _configs[k].listen << "\n";
		std::cout << std::setw(8)<< BLUE  << "server_name: " << RESET << _configs[k].server_name  << "\n";
		std::cout << std::setw(9)<< BLUE  << "error_page: " << RESET << _configs[k].error_page  << "\n";
		std::cout << std::setw(10)<< BLUE  << "cgi_alias: " << RESET;
		for(unsigned long c = 0; c < _configs[k].cgi_alias.size(); c++)
			std::cout << _configs[k].cgi_alias[c] << " ";
		std::cout << "\n";
		for(unsigned long l = 0; l < _configs[k].location.size(); l++)
		{
			std::cout << std::setw(14)<<  BLUE << "-------LOCATION[" << l << "]-------\n" << RESET;
			std::cout << std::setw(11)<< BLUE  << "location: " << RESET << _configs[k].location[l].location  << "\n";
			std::cout << std::setw(14)<< BLUE  << "index: " << RESET << _configs[k].location[l].index  << "\n";
			std::cout << std::setw(10)<< BLUE  << "autoindex: " << RESET << _configs[k].location[l].autoindex  << "\n";
			std::cout << std::setw(12)<< BLUE  << "methods: " << RESET;
			for(unsigned long m = 0; m < _configs[k].location[l].methods.size(); m++)
				std::cout << _configs[k].location[l].methods[m] << " ";
			std::cout << "\n";
			std::cout << std::setw(15)<< BLUE  << "root: " << RESET << _configs[k].location[l].root  << "\n";
		}
		enter("press ENTER to continue");
		std::cout << "\n";
	}
	std::cout << BLUE << "***************************************END\n" << RESET;
}






/*-------------------------------------------------------------------------------*/




void Config::createServers()
{

	/* 	
		поочередно запускаем серверы в количестве _numOfServers, 
	  	для каждого из серверов передаем соответствующую ему структуру с данными 
	*/

	pthread_t *threads;
	threads = new pthread_t[_numOfServers];
	std::cout << std::endl << CYAN_B << "Start servers..." << std::endl << CYAN <<"(enter \"exit\" for get out)" << RESET << std::endl << std::endl;
	sleep(1);
	for(int i = 0; i < _numOfServers; i++)
    {
		pthread_create(&threads[i], NULL, initServer<struct s_config, Server>, &_configs[i]);
    }
	pthread_create(&threads[_numOfServers], NULL, &cmds<Config>, &(*this));

	for (int i = 0; i < _numOfServers;)
	{
		pthread_join(threads[i++], NULL);
	}
}
