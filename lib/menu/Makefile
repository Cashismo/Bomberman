# Makefile for Irrlicht Examples
# It's usually sufficient to change just the target name and source file list
# and be sure that CXX is set to a valid compiler

# Name of the executable created (.exe will be added automatically if necessary)
Target = bomberman
# List of source files, separated by spaces
Sources = main.cpp Menu.cpp ConfFile.cpp
# Path to Irrlicht directory, should contain include/ and lib/
IrrlichtHome = ../..
# Path for the executable. Note that Irrlicht.dll should usually also be there for win32 systems
BinPath =

# general compiler settings (might need to be set when compiling the lib, too)
# preprocessor flags, e.g. defines and include paths
USERCPPFLAGS =
# compiler flags such as optimization flags
USERCXXFLAGS = -std=c++14 -O3 -ffast-math -g3
#USERCXXFLAGS = -g -Wall
# linker flags such as additional libraries and link paths
USERLDFLAGS =

####
#no changes necessary below this line
####

CPPFLAGS = -Iinclude -I/usr/X11R6/include $(USERCPPFLAGS)
CXXFLAGS = $(USERCXXFLAGS)
LDFLAGS = $(USERLDFLAGS)

#default target is Linux
all: all_linux

# target specific settings
all_linux all_win32 static_win32: LDFLAGS += -Llib/$(SYSTEM) -lIrrlicht
all_linux: LDFLAGS += -L/usr/X11R6/lib$(LIBSELECT) -lGL -lXxf86vm -lXext -lX11 -lXcursor
all_linux clean_linux: SYSTEM=Linux
all_win32 clean_win32 static_win32: SYSTEM=Win32-gcc
all_win32 clean_win32 static_win32: SUF=.exe
static_win32: CPPFLAGS += -D_IRR_STATIC_LIB_
all_win32: LDFLAGS += -lopengl32 -lm
static_win32: LDFLAGS += -lgdi32 -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lopengl32
# name of the binary - only valid for targets which set SYSTEM
DESTPATH = indie

all_linux all_win32 static_win32:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(Sources) -o $(Target) $(LDFLAGS)

clean: clean_linux

clean_linux:
	$(RM) $(DESTPATH)

.PHONY: all all_win32 static_win32 clean clean_linux

#multilib handling
ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif
#solaris real-time features
ifeq ($(HOSTTYPE), sun4)
LDFLAGS += -lrt
endif
