CXX = g++
CXX_FLAGS= -g -Wall -Wextra

SOURCES= main.cc\
		 text_viewer.cc\
		 header.cc\
		 marked_list.cc\
		 num_list.cc\
		 code_block.cc\
		 paragraph.cc\
		 line_break.cc\
		 containers.cc

OBJECTS= $(SOURCES:.cc=.o)

GENERATES= $(OBJECTS) smd

smd:	$(OBJECTS)
		$(CXX) $(CXX_FLAGS) $^ -o $@

%.o:	%.cc
		$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:	
		rm -f $(GENERATES)
