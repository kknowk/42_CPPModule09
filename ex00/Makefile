NAME = btc
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -MP
SRCS = main.cpp \
	BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)

DEPS = $(SRCS:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(NAME)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)