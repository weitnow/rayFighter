#!/bin/bash

# Function to recursively find and add header files
add_headers() {
    for file in $(find "$1" -type f -name "*.h"); do
        echo "// Including $file" >> BigSource.cpp
        cat "$file" >> BigSource.cpp
        echo -e "\n" >> BigSource.cpp
    done
}

# Function to recursively find and add source files
add_sources() {
    for file in $(find "$1" -type f -name "*.cpp"); do
        echo "// Including $file" >> BigSource.cpp
        cat "$file" >> BigSource.cpp
        echo -e "\n" >> BigSource.cpp
    done
}

# Check for parameters
if [ "$1" == "--generate" ]; then
    # Start with an empty file
    echo "// Combined source file" > BigSource.cpp

    # Specify the root directory (current directory or modify as needed)
    ROOT_DIR="."

    # Add all header files
    add_headers "$ROOT_DIR"

    # Add all source files
    add_sources "$ROOT_DIR"

    echo "BigSource.cpp has been generated."

elif [ "$1" == "--clean" ]; then
    # Remove the generated file
    if [ -f "BigSource.cpp" ]; then
        rm BigSource.cpp
        echo "BigSource.cpp has been deleted."
    else
        echo "BigSource.cpp does not exist."
    fi

else
    echo "Usage: $0 --generate | --clean"
fi
