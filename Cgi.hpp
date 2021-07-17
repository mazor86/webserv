
#ifndef CGI
# define CGI
# include "main.hpp"
# include "structure.h"
# include "Response.hpp"
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>


# define EXTENTION_WITH_INTERPRETER 1
# define EXTENTION_WITHOUT_INTERPRETER 0


/*
** для корректной работы cgi-модуля, все скрипты должны находиться в каталоге cgi_bin;
** в конфигурационном файле в cgi alias, указывать пути не ставя слеш в конце;
** в случае использования базового варианта доступа к скрипту (1), в атрибуте "href" тега <form>, 
** требуется указывать имя скрипта и релативный путь к нему: "/cgi_bin/script";
** в случае использования (2) и (3) вариантов доступа, в атрибуте "href" тега <form>, 
** требуется указывать имя скрипта без пути к нему;
** если скрипт написан на таких языках как python, php или perl, то расширение файла 
** должно быть ".py", ".php", ".perl" или ".pl" соответственно; 
** если скрипт написан на компилируемых языках, таких языках как С/С++,  то расширение файла  
** должно быть ".cgi" или ".exe"
**
*/



class Cgi
{
	private:
		std::vector<std::string> _vars; 				//переменные оркужения (string)
		char **_varsArray;								//переменные оркужения (char)


		struct s_config			*_config;				//конфиг
		std::string 			_body;					//боди при запросе POST
		std::string 			_pathToScript;			//путь к скрипту из html-формы
		std::string 			_fullPathToScript;		//полный путь к скрипту из корня сервера
		std::string             _pathToHandler;			//путь к обработчику скрипта
		std::string 			_date;					//дата и время инициализации скрипта

		
		struct stat _stat; 								/* получение данных о файле */


	public:
		Cgi(std::string body, struct s_config *config, std::string pathToScript, 
		std::map<std::string, std::string> requestHeaders, std::string requestMethod, std::string &date);
		Cgi(const Cgi &cgi);

		std::vector<std::string>  setVariables(std::map<std::string, std::string> requestHeaders, std::string requestMethod);
		char **getVarsArray(std::vector<std::string> vars);
		bool launchCGI();
		void addToDataBase();

};



#endif



// https://habr.com/ru/post/254621/
// http://angel07.webservis.ru/perl/env.html
// https://bez-logiki.ru/web-zapisi/zagolovki-zaprosov-i-otvetov-cgi
// http://massnet.narod.ru/chapter7.html
// https://russianblogs.com/article/48051026604/
// http://www.php.su/learnphp/cgi/?interface
// http://www.cyberguru.ru/web/web-programming/cgi-tutor.html?start=14
// http://www.xserver.ru/computer/langprogr/cgi/7/


