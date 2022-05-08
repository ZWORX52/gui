# Makefile for GUI program.

#CXX = g++
#CXX = clang++

EXE = main
OBJDIR = objdir/
IMGUI_DIR = ../imgui
CPPLINT_SOURCES = main.cpp encrypt.cpp utils.cpp origins.cpp astar.cpp main.hpp origins.hpp bf.cpp imgs.cpp
MY_SOURCES = main.cpp encrypt.cpp utils.cpp origins.cpp astar.cpp bf.cpp imgs.cpp
MY_OBJS = $(addprefix $(OBJDIR), $(addsuffix .o, $(basename $(notdir $(MY_SOURCES)))))
SOURCES = $(MY_SOURCES)
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJS = $(addprefix $(OBJDIR), $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += @g++.flags
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

all: buildable cls adddebugflaga imgui java

buildable:
	@if [ -d ../imgui ]; \
		then echo "Ready to build -- updating dear imgui!"; \
			cd ../imgui; \
			git pull; \
			cd ../gui; \
		else echo "Getting ready to build..."; \
			cd ..; \
			git clone https://github.com/ocornut/imgui; \
			echo "Cloning done! Ready to build..."; \
			cd gui; \
		fi;

cls:
	@clear

remake: cls clean adddebugflaga imgui

redebug: cls clean debug

rerelease: cls clean release

resmall: cls clean small

sremake: cls sclean adddebugflaga imgui

sredebug: cls sclean debug

srerelease: cls sclean release

sresmal: cls sclean small

debug: adddebugflaga adddebugflagb imgui

release: addreleaseflag imgui

small: addsmallflag imgui

adddebugflaga:
	$(eval CXXFLAGS += -g)

adddebugflagb:
	$(eval CXXFLAGS += -Og)

addreleaseflag:
	$(eval CXXFLAGS += -Ofast -Wno-strict-overflow)

addsmallflag:
	$(eval CXXFLAGS += -Os)

imgui: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(OBJS)

sclean:
	rm -f $(MY_OBJS)

java:
	@echo Will build java...

lint:
	cpplint $(CPPLINT_FLAGS) $(CPPLINT_SOURCES)

