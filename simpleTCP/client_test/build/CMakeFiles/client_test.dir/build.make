# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jiexu/simpleSocket/simpleTCP/client_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jiexu/simpleSocket/simpleTCP/client_test/build

# Include any dependencies generated for this target.
include CMakeFiles/client_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client_test.dir/flags.make

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o: /home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o -MF CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o.d -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp > CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.i

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.s

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o: /home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o -MF CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o.d -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp > CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.i

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.s

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o: /home/jiexu/simpleSocket/simpleTCP/common/Log.cpp
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o -MF CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o.d -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/common/Log.cpp

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/common/Log.cpp > CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.i

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/common/Log.cpp -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.s

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o: /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o -MF CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o.d -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp > CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.i

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.s

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o: /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o -MF CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o.d -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp > CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.i

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.s

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o: /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o -MF CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o.d -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp > CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.i

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.s

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o: /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o -MF CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o.d -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp > CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.i

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.s

CMakeFiles/client_test.dir/main.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/main.cpp.o: ../main.cpp
CMakeFiles/client_test.dir/main.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/client_test.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/main.cpp.o -MF CMakeFiles/client_test.dir/main.cpp.o.d -o CMakeFiles/client_test.dir/main.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/client_test/main.cpp

CMakeFiles/client_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/client_test/main.cpp > CMakeFiles/client_test.dir/main.cpp.i

CMakeFiles/client_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/client_test/main.cpp -o CMakeFiles/client_test.dir/main.cpp.s

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o: CMakeFiles/client_test.dir/flags.make
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o: /home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp
CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o: CMakeFiles/client_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o -MF CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o.d -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o -c /home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp > CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.i

CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp -o CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.s

# Object files for target client_test
client_test_OBJECTS = \
"CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o" \
"CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o" \
"CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o" \
"CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o" \
"CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o" \
"CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o" \
"CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o" \
"CMakeFiles/client_test.dir/main.cpp.o" \
"CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o"

# External object files for target client_test
client_test_EXTERNAL_OBJECTS =

/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Mutex.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myFunc.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/Log.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocket.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketClient.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketRD.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/client_IO/MySocketWD.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/main.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/home/jiexu/simpleSocket/simpleTCP/common/myThread.cpp.o
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/build.make
/home/jiexu/simpleSocket/simpleTCP/bin/client_test: CMakeFiles/client_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable /home/jiexu/simpleSocket/simpleTCP/bin/client_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client_test.dir/build: /home/jiexu/simpleSocket/simpleTCP/bin/client_test
.PHONY : CMakeFiles/client_test.dir/build

CMakeFiles/client_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_test.dir/clean

CMakeFiles/client_test.dir/depend:
	cd /home/jiexu/simpleSocket/simpleTCP/client_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiexu/simpleSocket/simpleTCP/client_test /home/jiexu/simpleSocket/simpleTCP/client_test /home/jiexu/simpleSocket/simpleTCP/client_test/build /home/jiexu/simpleSocket/simpleTCP/client_test/build /home/jiexu/simpleSocket/simpleTCP/client_test/build/CMakeFiles/client_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client_test.dir/depend

