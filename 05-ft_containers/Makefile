CXX=c++
CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -O3 -g
VPATH=tests:./
all: default_test vector stack set map

default_test: stl_default_test ft_default_test
vector: stl_vector_test ft_vector_test
stack: stl_stack_test ft_stack_test
set: stl_set_test ft_set_test
map: stl_map_test ft_map_test


stl_default_test : main.cpp; $(CXX) $(CXXFLAGS) -o stl_default_test $^
stl_vector_test : vector_test.cpp; $(CXX) $(CXXFLAGS) -o stl_vector_test $^
stl_stack_test : stack_test.cpp; $(CXX) $(CXXFLAGS) -o stl_stack_test $^
stl_set_test : stack_test.cpp; $(CXX) $(CXXFLAGS) -o stl_set_test $^
stl_map_test : map_test.cpp; $(CXX) $(CXXFLAGS) -o stl_map_test $^

ft_default_test : main.cpp; $(CXX) $(CXXFLAGS) -o ft_default_test $^ -D TEST
ft_vector_test : vector_test.cpp; $(CXX) $(CXXFLAGS) -o ft_vector_test $^ -D TEST
ft_stack_test : stack_test.cpp; $(CXX) $(CXXFLAGS) -o ft_stack_test $^ -D TEST
ft_set_test : stack_test.cpp; $(CXX) $(CXXFLAGS) -o ft_set_test $^ -D TEST
ft_map_test : map_test.cpp; $(CXX) $(CXXFLAGS) -o ft_map_test $^ -D TEST

clean:
	rm -f stl_default_test stl_vector_test stl_stack_test stl_set_test stl_map_test
	rm -f ft_default_test ft_vector_test ft_stack_test ft_set_test ft_map_test

fclean: clean

.PHONY: clean vector stack set map
