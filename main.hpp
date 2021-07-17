#ifndef GLOBAL_HPP
# define GLOBAL_HPP
# include <iostream>
# include <sstream>
# include <fstream>
# include <string>
# include <map>
# include <vector>
# include <iomanip>
# include <unistd.h>
# include <pthread.h>
# include <sys/errno.h>
# include <algorithm>

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# include "Socket.hpp"
# include "Connection.hpp"
# include "Config.hpp"
# include "RequestParser.hpp"
# include "Response.hpp"
# include "structure.h"


# define MAX_THREADS 3 /* ограничение допустимого количества потоков */





class Exceptions: public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return strerror(errno);
		}
};


# define RED  "\e[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define RED_B "\033[1;31m"
# define GREEN_B "\033[1;32m"
# define YELLOW_B "\e[1;33m"
# define BLUE_B "\033[1;34m"
# define PURPLE_B "\033[1;35m"
# define CYAN_B "\e[1;36m"
# define WHITE_B "\e[1;37m"
# define RESET "\033[0m"

# define READING 1
# define WRITING 2

# define WAIT 1
# define FULL 2
# define ERROR 3

#endif