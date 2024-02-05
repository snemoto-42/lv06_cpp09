# **************************************************************************** #
# Variables																	   #
# **************************************************************************** #

NAME	= RPN
SRCS	= $(shell echo *.cpp)
OBJDIR	= obj/
OBJS	= $(addprefix $(OBJDIR),$(SRCS:.cpp=.o)) 

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -pedantic -Wconversion
RM			= rm -f
RMD			= rm -rf

# **************************************************************************** #
# General Rules																   #
# **************************************************************************** #

all:	$(OBJDIR) $(NAME)

$(OBJDIR):
		mkdir -p obj

$(OBJDIR)%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
		${RMD} $(OBJDIR)

fclean:	clean
		${RM} ${NAME}

re:		fclean all

bonus:	all

.PHONY: all clean fclean re bonus
