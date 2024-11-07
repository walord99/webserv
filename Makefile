NAME            = 	webserv
FILES           =	main.cpp \
					classes/Connection.cpp \
					classes/Epoll_Wrapper.cpp \
					classes/Socket.cpp \
					classes/Server_Socket.cpp \
					classes/Server.cpp \
					classes/ProtocolInterface.cpp \
					classes/HttpProtocol.cpp

SRC_DIR         = 	src
OBJ_DIR         = 	obj
SRC             = 	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ             = 	$(addprefix $(OBJ_DIR)/, $(FILES:.cpp=.o))
CC              = 	g++
HEADER_DIR      = 	include

INCLUDES        = 	-I$(HEADER_DIR)

ERROR_FLAGS     = 	-Werror -Wall -Wextra -std=c++98

all: $(NAME)
$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIB_FLAGS) -o $(NAME) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if [ ! -d $(dir $@) ]; then \
        mkdir -p $(dir $@); \
    fi
	$(CC) $(CC_DEBUG) $(INCLUDES) $(ERROR_FLAGS) -c $< -o $@ -g 

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re