# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /nix/store/mfrfb675a16gqchycqv16aziivn09dxa-cmake-3.31.3/bin/cmake

# The command to remove a file.
RM = /nix/store/mfrfb675a16gqchycqv16aziivn09dxa-cmake-3.31.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stoat/interview/test-repo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stoat/interview/test-repo/build

# Include any dependencies generated for this target.
include CMakeFiles/testproj.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testproj.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testproj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testproj.dir/flags.make

CMakeFiles/testproj.dir/codegen:
.PHONY : CMakeFiles/testproj.dir/codegen

CMakeFiles/testproj.dir/main.cpp.o: CMakeFiles/testproj.dir/flags.make
CMakeFiles/testproj.dir/main.cpp.o: /home/stoat/interview/test-repo/main.cpp
CMakeFiles/testproj.dir/main.cpp.o: CMakeFiles/testproj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stoat/interview/test-repo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testproj.dir/main.cpp.o"
	/nix/store/591apldfgm1gr238rbfc8ib0y1z8ng2y-gcc-wrapper-14-20241116/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testproj.dir/main.cpp.o -MF CMakeFiles/testproj.dir/main.cpp.o.d -o CMakeFiles/testproj.dir/main.cpp.o -c /home/stoat/interview/test-repo/main.cpp

CMakeFiles/testproj.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testproj.dir/main.cpp.i"
	/nix/store/591apldfgm1gr238rbfc8ib0y1z8ng2y-gcc-wrapper-14-20241116/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stoat/interview/test-repo/main.cpp > CMakeFiles/testproj.dir/main.cpp.i

CMakeFiles/testproj.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testproj.dir/main.cpp.s"
	/nix/store/591apldfgm1gr238rbfc8ib0y1z8ng2y-gcc-wrapper-14-20241116/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stoat/interview/test-repo/main.cpp -o CMakeFiles/testproj.dir/main.cpp.s

CMakeFiles/testproj.dir/candle.cpp.o: CMakeFiles/testproj.dir/flags.make
CMakeFiles/testproj.dir/candle.cpp.o: /home/stoat/interview/test-repo/candle.cpp
CMakeFiles/testproj.dir/candle.cpp.o: CMakeFiles/testproj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stoat/interview/test-repo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testproj.dir/candle.cpp.o"
	/nix/store/591apldfgm1gr238rbfc8ib0y1z8ng2y-gcc-wrapper-14-20241116/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testproj.dir/candle.cpp.o -MF CMakeFiles/testproj.dir/candle.cpp.o.d -o CMakeFiles/testproj.dir/candle.cpp.o -c /home/stoat/interview/test-repo/candle.cpp

CMakeFiles/testproj.dir/candle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testproj.dir/candle.cpp.i"
	/nix/store/591apldfgm1gr238rbfc8ib0y1z8ng2y-gcc-wrapper-14-20241116/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stoat/interview/test-repo/candle.cpp > CMakeFiles/testproj.dir/candle.cpp.i

CMakeFiles/testproj.dir/candle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testproj.dir/candle.cpp.s"
	/nix/store/591apldfgm1gr238rbfc8ib0y1z8ng2y-gcc-wrapper-14-20241116/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stoat/interview/test-repo/candle.cpp -o CMakeFiles/testproj.dir/candle.cpp.s

# Object files for target testproj
testproj_OBJECTS = \
"CMakeFiles/testproj.dir/main.cpp.o" \
"CMakeFiles/testproj.dir/candle.cpp.o"

# External object files for target testproj
testproj_EXTERNAL_OBJECTS =

testproj: CMakeFiles/testproj.dir/main.cpp.o
testproj: CMakeFiles/testproj.dir/candle.cpp.o
testproj: CMakeFiles/testproj.dir/build.make
testproj: CMakeFiles/testproj.dir/compiler_depend.ts
testproj: CMakeFiles/testproj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/stoat/interview/test-repo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable testproj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testproj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testproj.dir/build: testproj
.PHONY : CMakeFiles/testproj.dir/build

CMakeFiles/testproj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testproj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testproj.dir/clean

CMakeFiles/testproj.dir/depend:
	cd /home/stoat/interview/test-repo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stoat/interview/test-repo /home/stoat/interview/test-repo /home/stoat/interview/test-repo/build /home/stoat/interview/test-repo/build /home/stoat/interview/test-repo/build/CMakeFiles/testproj.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/testproj.dir/depend

