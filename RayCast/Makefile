EXE = App
IMGUI = ./includes/imgui
STBI = ./includes/stbi
RENDER = ./Render
INCLUDES = ./includes
RENDER_DIR = ./Render
SOURCES = App.cpp
SOURCES += $(INCLUDES)/ImGuiContext.cpp $(IMGUI)/imgui.cpp $(IMGUI)/imgui_demo.cpp $(IMGUI)/imgui_draw.cpp $(IMGUI)/imgui_tables.cpp $(IMGUI)/imgui_widgets.cpp
SOURCES += $(IMGUI)/imgui_impl_glfw.cpp $(IMGUI)/imgui_impl_opengl3.cpp
SOURCES += $(RENDER)/VAO.cpp $(RENDER)/VBO.cpp $(RENDER)/EBO.cpp $(RENDER)/Raycast.cpp $(RENDER)/Shader.cpp
SOURCES += $(STBI)/stb_image.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL -lGLEW

CXXFLAGS = -std=c++11 -I$(INCLUDES) -I$(RENDER_DIR)
CXXFLAGS += -g -Wall -Wformat -pthread
LIBS =

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
		LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
		CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW"
		LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += -L$(shell pwd)
	CXXFLAGS += `pkg-config --cflags glfw3`
		CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(RENDER)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(INCLUDES)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<
	
%.o:$(IMGUI)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(STBI)/%.cpp
		$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
		@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
		$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
		rm -f $(EXE) $(OBJS)
