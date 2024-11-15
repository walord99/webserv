NAME            = 	webserv
FILES           =	main.cpp \
					\
					Socket/Socket.cpp \
					Socket/ServerSocket/ServerSocket.cpp \
					Socket/Connection/Connection.cpp \
					\
					Protocols/IProtocol.cpp \
					Protocols/IProtocolFactory.cpp \
					Protocols/Http/HttpProtocol.cpp \
					Protocols/Http/HttpFactory.cpp \
					\
					EpollWrapper/EpollWrapper.cpp \
					\
					Server/Server.cpp \

SRC_DIR         = 	src
OBJ_DIR         = 	obj
SRC             = 	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ             = 	$(addprefix $(OBJ_DIR)/, $(FILES:.cpp=.o))
CC              = 	g++

DIRS			=	${shell find src/ -type d -print}
INCLUDES        = 	$(addprefix -I, $(DIRS))

ERROR_FLAGS     = 	-Werror -Wall -Wextra -std=c++98

all: $(NAME)
$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(LIB_FLAGS) -o $(NAME) 
	@echo $(CC) "<obj>" $(LIB_FLAGS) -o $(NAME) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if [ ! -d $(dir $@) ]; then \
        mkdir -p $(dir $@); \
    fi
	@$(CC) $(CC_DEBUG) $(INCLUDES) $(ERROR_FLAGS) -c $< -o $@ -g 
	@echo $(CC) $(CC_DEBUG) "<includes>" $(ERROR_FLAGS) -c $< -o $@ -g 

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re