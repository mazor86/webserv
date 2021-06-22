
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
<<<<<<< HEAD

	int	port1 = 8181;
	Server server;
=======
	std::string cmd;
	while(1)
	{
		std::cout  << std::endl << CYAN_B << "webserv: " << CYAN << "do you want to see config? (y/n)" << RESET << std::endl;
		std::cin >> cmd;
		if (cmd == "y") { enter(""); config.showConfig(); break ; }
		if (cmd == "n") { break ;}
		else { std::cout  << CYAN_B << "webserv: " << CYAN << "please, enter \"y\" or \"n\"" << RESET << std::endl; }
	}

	/*-------------------------------------------------------------------------------*/
	

	config.createServers();  //запускаем сервера


	return 0;
>>>>>>> fb9a0e460b329e37b10651ee006a9a85775627cd
}