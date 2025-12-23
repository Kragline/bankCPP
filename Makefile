NAME = bankshell

CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

HEADER_DIR = include/
SOURCES_DIR = sources/
OBJECTS_DIR = objects/

FILENAMES = Account Bank input main

SOURCES = $(addsuffix .c, $(addprefix $(SOURCES_DIR), $(FILENAMES)))
OBJECTS = $(addsuffix .o, $(addprefix $(OBJECTS_DIR), $(FILENAMES)))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CPP) $(CPP_FLAGS) -I$(HEADER_DIR) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.cpp | $(OBJECTS_DIR)
	$(CPP) -c $(CPP_FLAGS) -I$(HEADER_DIR) $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re