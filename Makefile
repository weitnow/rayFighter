#############
# VARIABLES #
#############

DEBUG ?= 1
ENABLE_WARNINGS ?= 1
WARNINGS_AS_ERRORS ?= 0
OS_WINDOWS ?= 0

BUILD_DIR = build

ifeq ($(ENABLE_WARNINGS), 1)
CXX_WARNINGS = -Wall -Wextra -Wpedantic
else
CXX_WARNINGS =
endif

ifeq ($(WARNINGS_AS_ERRORS), 1)
CXX_WARNINGS += -Werror
endif

CXX_STANDARD = c++17
CXX = g++
CXXFLAGS = $(CXX_WARNINGS) -std=$(CXX_STANDARD)

# Additional flags to specify the directories to search for header files
CPPFLAGS = -I Assets -I Characters -I GameObjects -I Utils

LDFLAGS =

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -O0
EXECUTABLE_NAME = mainDebug
else
CXXFLAGS += -O3
EXECUTABLE_NAME = mainRelease
endif

ifeq ($(OS_WINDOWS), 1)
USED_LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
else
USED_LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

COMPILER_CALL = $(CXX) $(CXXFLAGS)

# Recursively find all .cpp files in subdirectories
CXX_SOURCES := $(wildcard */*.cpp)
# Include .cpp files in the root directory
CXX_SOURCES += $(wildcard *.cpp)

CXX_OBJECTS = $(patsubst %.cc, $(BUILD_DIR)%.o, $(CXX_SOURCES))

###########
# TARGETS #
###########

build: create_dir $(CXX_OBJECTS)
	$(COMPILER_CALL) $(CXX_OBJECTS) $(USED_LIBS) -o $(BUILD_DIR)/$(EXECUTABLE_NAME)

create_dir:
	mkdir -p build

run: build
ifeq ($(OS_WINDOWS), 1)
	./$(BUILD_DIR)/$(EXECUTABLE_NAME).exe
else
	./$(BUILD_DIR)/$(EXECUTABLE_NAME)
endif

start:
ifeq ($(OS_WINDOWS), 1)
	./$(BUILD_DIR)/$(EXECUTABLE_NAME).exe & powershell -Command "Start-Sleep -Seconds 1; Get-Process -Name $(EXECUTABLE_NAME) | Select-Object WorkingSet64"
else
	/usr/bin/time -v ./$(BUILD_DIR)/$(EXECUTABLE_NAME)
endif


clean:
	rm -f $(BUILD_DIR)/*.o
ifeq ($(OS_WINDOWS), 1)
	rm -f $(BUILD_DIR)/$(EXECUTABLE_NAME).exe
else
	rm -f $(BUILD_DIR)/$(EXECUTABLE_NAME)
endif

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BUILD_DIR)/$(EXECUTABLE_NAME)


############
# PATTERNS #
############
# Regel wie aus einer cpp-datei eine .o datei wird
# $@: = %.ccp 	-> the file name of the target
# $<: = %.o 	-> the name of the first dependency
%.o: %.cpp
	$(COMPILER_CALL) $(USED_LIBS) -c $< -o $@


#########
# PHONY #
#########
.PHONY: create_dir build run clean
