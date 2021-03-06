
#include "Config.hpp"




int	main(int argc, char **argv)
{
	Config config(DEFAULT_CONFIG_PATH);
	std::cout << CYAN_B << "Reading config..." << RESET << std::endl << std::endl;
	sleep(1);
	if (argc > 2)
	{
		std::cout << std::endl << YELLOW << "error: wrong number of arguments\n" << RESET << std::endl;
		std::cout << BLUE << "usage: " << std::endl << std::setw(12) << BLUE_B << "./webserv" 
		<< BLUE << " or" << std::endl << std::setw(12) << BLUE_B << "./webserv [path_to_configuration_file]" << RESET << std::endl << std::endl;
		return 1;
	}
	else if (argc == 2)
		config.load(std::string(argv[1]));
	else
		config.load(config.getPath());
	if (!config.isValid())
	{
		std::cout << CYAN << "webserv: please, check configuration file" << RESET << std::endl << std::endl;
		return 1;
	}

	std::string cmd;
	while(1)
	{
		std::cout  << std::endl << CYAN_B << "webserv: " << CYAN << "do you want to see config? (y/n)" << RESET << std::endl;
		std::cin >> cmd;
		if (cmd == "y") { enter(""); config.showConfig(); break ; }
		if (cmd == "n") { break ;}
		else { std::cout  << CYAN_B << "webserv: " << CYAN << "please, enter \"y\" or \"n\"" << RESET << std::endl; }
	}
	std::ifstream iff("www/response.log");
	if(iff.bad() == false) /* удаляем старый log-файл если он существует */
		std::remove("www/response.log");

	/*-------------------------------------------------------------------------------*/

	try
	{
		config.createServers();  /* запускаем сервера */
	}
	catch (std::exception &e)
	{
		std::cout << RED << e.what() << RESET << std::endl;
		return 1;
	}

	return 0;
}