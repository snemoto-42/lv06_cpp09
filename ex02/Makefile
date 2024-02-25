# **************************************************************************** #
# Variables																	   #
# **************************************************************************** #

NAME	= PmergeMe
SRCS	= $(wildcard *.cpp)
OBJDIR	= obj/
OBJS	= $(addprefix $(OBJDIR),$(SRCS:.cpp=.o))
DEPENDS = $(OBJS:.o=.d)

CXX			= 	c++
CXXFLAGS	= 	-MMD -MP \
				-Wall -Wextra -Werror \
				-std=c++98 -pedantic
RMD			= 	rm -rf

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

-include $(DEPENDS)

clean:
		${RMD} $(OBJDIR)

fclean:	clean
		${RM} ${NAME}

re:		fclean all

bonus:	all

do:		
		./test.sh

.PHONY: all clean fclean re bonus do
