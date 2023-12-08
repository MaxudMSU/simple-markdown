CXX = g++
CXX_FLAGS= -g -Wall -Wextra

SOURCES= main.cpp\
		 text_viewer.cpp\
		 header.cpp\
		 marked_list.cpp\
		 num_list.cpp\
		 code_block.cpp\
		 paragraph.cpp\
		 line_break.cpp\
		 containers.cpp

OBJECTS= $(SOURCES:.cpp=.o)

GENERATES= $(OBJECTS) smd

smd:	$(OBJECTS)
		$(CXX) $(CXX_FLAGS) $^ -o $@

%.o:	%.cpp
		$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:	
		rm -f $(GENERATES)
