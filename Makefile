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
CPPFLAGS = -I Assets -I Characters -I./GameObjects -I./Utils

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

COMPILER_CALL = $(CXX) $(CPPFLAGS) $(CXXFLAGS)

# Recursively find all .cpp files in subdirectories
ifeq ($(OS_WINDOWS), 1)
    CXX_SOURCES := $(shell powershell -Command "Get-ChildItem -Recurse -Include *.cpp | Select-Object -ExpandProperty FullName")
    CXX_SOURCES := $(subst \,/,$(CXX_SOURCES)) # Normalize Windows paths
else
    CXX_SOURCES := $(shell find . -path ./cmake-build-debug -prune -o -name '*.cpp' -print)

endif

# Print CXX_SOURCES for debugging
$(info CXX_SOURCES: $(CXX_SOURCES))

# Create object file names based on source file names and directory structure
ifeq ($(OS_WINDOWS), 1)
	CXX_OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(subst $(CURDIR)/,,$(CXX_SOURCES)))
else
	CXX_OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CXX_SOURCES))
endif

# Print CXX_OBJECTS for debugging
$(info CXX_OBJECTS: $(CXX_OBJECTS))

###########
# TARGETS #
###########

build: create_dir $(CXX_OBJECTS)
	$(info CXX_OBJECTS: $(CXX_OBJECTS))
	@echo "Compiling with: $(COMPILER_CALL) $(CXX_OBJECTS) $(LDFLAGS) $(USED_LIBS) -o $(BUILD_DIR)/$(EXECUTABLE_NAME)"
	$(COMPILER_CALL) $(CXX_OBJECTS) $(LDFLAGS) $(USED_LIBS) -o $(BUILD_DIR)/$(EXECUTABLE_NAME)

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
	rm -f $(BUILD_DIR)/*.d
ifeq ($(OS_WINDOWS), 1)
	@powershell -Command "Get-ChildItem -Path '$(BUILD_DIR)\**\*.o' -Recurse -Force | Remove-Item -Force"
	rm -f $(BUILD_DIR)/$(EXECUTABLE_NAME).exe
else
	find $(BUILD_DIR) -name "*.o" -delete
	rm -f $(BUILD_DIR)/$(EXECUTABLE_NAME)
endif

rebuild: clean build

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BUILD_DIR)/$(EXECUTABLE_NAME)

valgrind-definite: build
	valgrind --leak-check=full --errors-for-leak-kinds=definite ./$(BUILD_DIR)/$(EXECUTABLE_NAME)


runlimitedcpu:
	cpulimit -l 10 ./$(BUILD_DIR)/$(EXECUTABLE_NAME)


############
# PATTERNS #
############
# Rule to create object files, preserving directory structure
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(COMPILER_CALL) -c $< -o $@

#########
# PHONY #
#########
.PHONY: create_dir build run clean valgrind
