CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = ex01

SRCDIR = src
INCDIR = includes
OBJDIR = obj

INCLUDES = -I$(INCDIR)

SOURCES = main.cpp Fixed.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

SRCFILES = $(SOURCES:%.cpp=$(SRCDIR)/%.cpp)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
