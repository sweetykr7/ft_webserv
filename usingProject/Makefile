NAME = webserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98


SRCS_DIR = ./srcs



SRCS = $(SRCS_DIR)/main.cpp

OBJS = $(SRCS:.cpp=.o)


$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

all : $(NAME)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re