#!/bin/bash

# Create the build directory if it doesn't exist
mkdir -p build

# Compile the project
g++ -h -o build/server main.cpp src/api/testing.cpp src/server/server_lib.cpp src/server/static.cpp src/server/file_parser.cpp src/server/ipv4.cpp src/server/request.cpp src/server/response.cpp src/server/router.cpp src/server/server.cpp src/server/string_utils.cpp -Iinclude

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable created at build/server"
else
    echo "Compilation failed."
fi