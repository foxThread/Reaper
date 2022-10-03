#**************************************************************************************************
#
#   raylib makefile for Desktop platforms, Raspberry Pi, Android and HTML5
#
#   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
#
#   This software is provided "as-is", without any express or implied warranty. In no event
#   will the authors be held liable for any damages arising from the use of this software.
#
#   Permission is granted to anyone to use this software for any purpose, including commercial
#   applications, and to alter it and redistribute it freely, subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not claim that you
#     wrote the original software. If you use this software in a product, an acknowledgment
#     in the product documentation would be appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not be misrepresented
#     as being the original software.
#
#     3. This notice may not be removed or altered from any source distribution.
#
#**************************************************************************************************

.PHONY: all clean

# Define required environment variables
#------------------------------------------------------------------------------------------------
# Define target platform: PLATFORM_DESKTOP, PLATFORM_RPI, PLATFORM_DRM, PLATFORM_ANDROID, PLATFORM_WEB
SRC_DIR=.
PLATFORM              = PLATFORM_DESKTOP

# Define required raylib variables
PROJECT_NAME          = game
RAYLIB_VERSION        = 4.2.0
RAYLIB_PATH           = e:/tools/raylib/raylib


# Library type compilation: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE        = STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            = RELEASE

# Use external GLFW library instead of rglfw module
USE_EXTERNAL_GLFW     = FALSE

# Use Wayland display server protocol on Linux desktop (by default it uses X11 windowing system)
# NOTE: This variable is only used for PLATFORM_OS: LINUX
USE_WAYLAND_DISPLAY   = FALSE

PLATFORM_OS = WINDOWS
   




# Define raylib release directory for compiled library
RAYLIB_RELEASE_PATH 	= $(RAYLIB_PATH)/src



# Define default C compiler: CC
#------------------------------------------------------------------------------------------------
CC = g++


# Define default make program: MAKE
#------------------------------------------------------------------------------------------------
 MAKE = mingw32-make



# Define compiler flags: CFLAGS
#------------------------------------------------------------------------------------------------
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -s                   strip unnecessary data from build
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -Wno-unused-value    ignore unused return values of some functions (i.e. fread())
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result 

ifeq ($(BUILD_MODE),DEBUG)
	CFLAGS += -g -D_DEBUG
	CFLAGS += -s -O1
	endif


# Additional flags for compiler (if desired)
#  -Wextra                  enables some extra warning flags that are not enabled by -Wall
#  -Wmissing-prototypes     warn if a global function is defined without a previous prototype declaration
#  -Wstrict-prototypes      warn if a function is declared or defined without specifying the argument types
#  -Werror=implicit-function-declaration   catch function calls without prior declaration
#CFLAGS += -Wextra -Wmissing-prototypes -Wstrict-prototypes

	


# Define include paths for required headers: INCLUDE_PATHS
# NOTE: Some external/extras libraries could be required (stb, easings...)
#------------------------------------------------------------------------------------------------
INCLUDE_PATHS = -I. -I./include -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external

# Define library paths containing required libs: LDFLAGS
#------------------------------------------------------------------------------------------------
LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src
LDFLAGS += -Wl,--subsystem,windows
#LDFLAGS += $(RAYLIB_PATH)/src/raylib.rc.data
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm



ifeq ($(USE_WAYLAND_DISPLAY),TRUE)
	LDLIBS += -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon
endif
	   

OBJ_DIR=OBJ
SRC_DIR=SRC

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

DEPENDS := $(patsubst %.cpp,$(OBJ_DIR)/%.d,$(SOURCES))

.PHONY: all clean
all:main

clean:
	$(RM) $(OBJS) $(DEPENDS) main

main: $(OBJS)
	g++ -o $@ $^ $(CFLAGS)  $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D $(PLATFORM)












-include $(DEPENDS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp Makefile 
	g++ -c -o $@  $^ $(CFLAGS)  -MMD $(INCLUDE_PATHS) -D $(PLATFORM) 








# Define source code object files required
#------------------------------------------------------------------------------------------------
#PROJECT_SOURCE_FILES = $(wildcard $(SRC_DIR)/*.cpp)


# Define processes to execute
#------------------------------------------------------------------------------------------------
# Default target entry
#OBJS = $(patsubst %.cpp, %.o, $(PROJECT_SOURCE_FILES))
#all: $(MAKE)
#$(PROJECT_NAME):$(OBJS) 
#    $(CC) -o $(PROJECT_NAME) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)
#%.o: %.c*
 #   $(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

#clean:
 #   del *.o *.exe /s






