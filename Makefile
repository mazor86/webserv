
NAME = webserv

CC = clang++

# -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp Config.cpp Server.cpp RequestParser.cpp Response.cpp Connection.cpp Socket.cpp Cgi.cpp

OBJS = $(SRCS:.cpp=.o)

#COLORS
RED = \033[1;31m
GREEN = \033[0;32m
GREEN_BOLD= \033[1;32m
YELLOW= \033[0;33m
BLUE = \033[0;34m
BLUE_BOLD= \033[1;34m
CYAN = \033[0;36m
PURPLE = \033[0;35m
PURPLE_BOLD = \033[1;35m
RESET = \033[0m
#-fsanitize=address

all: $(NAME)
	
%.o: %.cpp %.hpp
	@echo "$(GREEN)Compiling...$(RESET)"
	@sleep 0.2
	@$(CC) $(CFLAGS)  -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -pthread -g
	@echo "$(GREEN_BOLD)Completed!$(RESET)"
	@echo "$(BLUE_BOLD)=======WEBSERV/arannara_team/21school=======$(RESET)"
	@echo " $(PURPLE)Directories:$(RESET)"
	@echo " $(PURPLE)1.$(RESET) $(CYAN)/config/$(RESET) - файлы конфигураций"
	@echo " $(PURPLE)2.$(RESET) $(CYAN)/www/$(RESET) - основной раздел для контента"
	@echo " $(PURPLE)3.$(RESET) $(CYAN)/www/default/$(RESET) - директория служебных станиц (errors, etc)"
	@echo " $(PURPLE)4.$(RESET) $(CYAN)/www/site.com/$(RESET) - сайт-пример установленный по умолчанию"
	@echo " $(PURPLE)5.$(RESET) $(CYAN)/www/YourSite.com/$(RESET) - "новые разделы необходимо размещать в каталоге www
	@echo " $(PURPLE)use $(PURPLE_BOLD)./webserv $(PURPLE)for start program$(RESET)"
	@echo " $(PURPLE)or $(PURPLE_BOLD)./webserv [path_to_configuration_file]$(PURPLE) to run with your configuration file$(RESET)"


clean:
	$(RM) ./*.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
