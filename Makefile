# Makefile for GUI program.

#CXX = g++
#CXX = clang++

EXE = main
OBJDIR = objdir/
IMGUI_DIR = ../imgui
CPPLINT_SOURCES = main.cpp encrypt.cpp utils.cpp origins.cpp astar.cpp main.hpp origins.hpp
SOURCES = main.cpp encrypt.cpp utils.cpp origins.cpp astar.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJS = $(addprefix $(OBJDIR), $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wextra -Wpedantic -Werror -Wformat 
CPPLINT_FLAGS = --linelength=120
LIBS = -lgmp

##---------------------------------------------------------------------
## OPENGL ES
##---------------------------------------------------------------------

## This assumes a GL ES library available in the system, e.g. libGLESv2.so
# CXXFLAGS += -DIMGUI_IMPL_OPENGL_ES2
# LINUX_GL_LIBS = -lGLESv2

ECHO_MESSAGE = "Linux"
LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

CXXFLAGS += `pkg-config --cflags glfw3`
CFLAGS = $(CXXFLAGS)

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

$(OBJDIR)%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: imgui java

run:
	@c;make&&./main

test: imgui
	@if ./main; then make lint; else make debug; fi

lint:
	cpplint $(CPPLINT_FLAGS) $(CPPLINT_SOURCES)
	@cpplint $(CPPLINT_FLAGS) --output=sed $(CPPLINT_SOURCES) > changes.sed
	@echo Wrote changes to 'changes.sed'

debug: imgui
	valgrind ./main
	gdb main

imgui: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

cleanf:
	rm -f $(EXE) $(OBJS)

clean:
	rm -f $(OBJS)

java:
	@echo Will build java...

