# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /home/crylia/Dokumente/git/QutieFM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/crylia/Dokumente/git/QutieFM/debug

# Utility rule file for QutieFM_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/QutieFM_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/QutieFM_autogen.dir/progress.make

CMakeFiles/QutieFM_autogen: QutieFM_autogen/timestamp

QutieFM_autogen/timestamp: /usr/lib/qt6/moc
QutieFM_autogen/timestamp: /usr/lib/qt6/uic
QutieFM_autogen/timestamp: CMakeFiles/QutieFM_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/crylia/Dokumente/git/QutieFM/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target QutieFM"
	/usr/bin/cmake -E cmake_autogen /home/crylia/Dokumente/git/QutieFM/debug/CMakeFiles/QutieFM_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/crylia/Dokumente/git/QutieFM/debug/QutieFM_autogen/timestamp

QutieFM_autogen: CMakeFiles/QutieFM_autogen
QutieFM_autogen: QutieFM_autogen/timestamp
QutieFM_autogen: CMakeFiles/QutieFM_autogen.dir/build.make
.PHONY : QutieFM_autogen

# Rule to build all files generated by this target.
CMakeFiles/QutieFM_autogen.dir/build: QutieFM_autogen
.PHONY : CMakeFiles/QutieFM_autogen.dir/build

CMakeFiles/QutieFM_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QutieFM_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QutieFM_autogen.dir/clean

CMakeFiles/QutieFM_autogen.dir/depend:
	cd /home/crylia/Dokumente/git/QutieFM/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/crylia/Dokumente/git/QutieFM /home/crylia/Dokumente/git/QutieFM /home/crylia/Dokumente/git/QutieFM/debug /home/crylia/Dokumente/git/QutieFM/debug /home/crylia/Dokumente/git/QutieFM/debug/CMakeFiles/QutieFM_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/QutieFM_autogen.dir/depend

