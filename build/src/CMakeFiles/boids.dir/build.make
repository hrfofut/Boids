# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /v/filer4b/v38q001/jfish7/Documents/Graphics/boids

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build

# Include any dependencies generated for this target.
include src/CMakeFiles/boids.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/boids.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/boids.dir/flags.make

src/CMakeFiles/boids.dir/procedure_geometry.cc.o: src/CMakeFiles/boids.dir/flags.make
src/CMakeFiles/boids.dir/procedure_geometry.cc.o: ../src/procedure_geometry.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/boids.dir/procedure_geometry.cc.o"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/boids.dir/procedure_geometry.cc.o -c /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/procedure_geometry.cc

src/CMakeFiles/boids.dir/procedure_geometry.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boids.dir/procedure_geometry.cc.i"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/procedure_geometry.cc > CMakeFiles/boids.dir/procedure_geometry.cc.i

src/CMakeFiles/boids.dir/procedure_geometry.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boids.dir/procedure_geometry.cc.s"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/procedure_geometry.cc -o CMakeFiles/boids.dir/procedure_geometry.cc.s

src/CMakeFiles/boids.dir/procedure_geometry.cc.o.requires:
.PHONY : src/CMakeFiles/boids.dir/procedure_geometry.cc.o.requires

src/CMakeFiles/boids.dir/procedure_geometry.cc.o.provides: src/CMakeFiles/boids.dir/procedure_geometry.cc.o.requires
	$(MAKE) -f src/CMakeFiles/boids.dir/build.make src/CMakeFiles/boids.dir/procedure_geometry.cc.o.provides.build
.PHONY : src/CMakeFiles/boids.dir/procedure_geometry.cc.o.provides

src/CMakeFiles/boids.dir/procedure_geometry.cc.o.provides.build: src/CMakeFiles/boids.dir/procedure_geometry.cc.o

src/CMakeFiles/boids.dir/render_pass.cc.o: src/CMakeFiles/boids.dir/flags.make
src/CMakeFiles/boids.dir/render_pass.cc.o: ../src/render_pass.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/boids.dir/render_pass.cc.o"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/boids.dir/render_pass.cc.o -c /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/render_pass.cc

src/CMakeFiles/boids.dir/render_pass.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boids.dir/render_pass.cc.i"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/render_pass.cc > CMakeFiles/boids.dir/render_pass.cc.i

src/CMakeFiles/boids.dir/render_pass.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boids.dir/render_pass.cc.s"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/render_pass.cc -o CMakeFiles/boids.dir/render_pass.cc.s

src/CMakeFiles/boids.dir/render_pass.cc.o.requires:
.PHONY : src/CMakeFiles/boids.dir/render_pass.cc.o.requires

src/CMakeFiles/boids.dir/render_pass.cc.o.provides: src/CMakeFiles/boids.dir/render_pass.cc.o.requires
	$(MAKE) -f src/CMakeFiles/boids.dir/build.make src/CMakeFiles/boids.dir/render_pass.cc.o.provides.build
.PHONY : src/CMakeFiles/boids.dir/render_pass.cc.o.provides

src/CMakeFiles/boids.dir/render_pass.cc.o.provides.build: src/CMakeFiles/boids.dir/render_pass.cc.o

src/CMakeFiles/boids.dir/main.cc.o: src/CMakeFiles/boids.dir/flags.make
src/CMakeFiles/boids.dir/main.cc.o: ../src/main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/boids.dir/main.cc.o"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/boids.dir/main.cc.o -c /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/main.cc

src/CMakeFiles/boids.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boids.dir/main.cc.i"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/main.cc > CMakeFiles/boids.dir/main.cc.i

src/CMakeFiles/boids.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boids.dir/main.cc.s"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/main.cc -o CMakeFiles/boids.dir/main.cc.s

src/CMakeFiles/boids.dir/main.cc.o.requires:
.PHONY : src/CMakeFiles/boids.dir/main.cc.o.requires

src/CMakeFiles/boids.dir/main.cc.o.provides: src/CMakeFiles/boids.dir/main.cc.o.requires
	$(MAKE) -f src/CMakeFiles/boids.dir/build.make src/CMakeFiles/boids.dir/main.cc.o.provides.build
.PHONY : src/CMakeFiles/boids.dir/main.cc.o.provides

src/CMakeFiles/boids.dir/main.cc.o.provides.build: src/CMakeFiles/boids.dir/main.cc.o

src/CMakeFiles/boids.dir/gui.cc.o: src/CMakeFiles/boids.dir/flags.make
src/CMakeFiles/boids.dir/gui.cc.o: ../src/gui.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/boids.dir/gui.cc.o"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/boids.dir/gui.cc.o -c /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/gui.cc

src/CMakeFiles/boids.dir/gui.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boids.dir/gui.cc.i"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/gui.cc > CMakeFiles/boids.dir/gui.cc.i

src/CMakeFiles/boids.dir/gui.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boids.dir/gui.cc.s"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/gui.cc -o CMakeFiles/boids.dir/gui.cc.s

src/CMakeFiles/boids.dir/gui.cc.o.requires:
.PHONY : src/CMakeFiles/boids.dir/gui.cc.o.requires

src/CMakeFiles/boids.dir/gui.cc.o.provides: src/CMakeFiles/boids.dir/gui.cc.o.requires
	$(MAKE) -f src/CMakeFiles/boids.dir/build.make src/CMakeFiles/boids.dir/gui.cc.o.provides.build
.PHONY : src/CMakeFiles/boids.dir/gui.cc.o.provides

src/CMakeFiles/boids.dir/gui.cc.o.provides.build: src/CMakeFiles/boids.dir/gui.cc.o

src/CMakeFiles/boids.dir/Flock.cpp.o: src/CMakeFiles/boids.dir/flags.make
src/CMakeFiles/boids.dir/Flock.cpp.o: ../src/Flock.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/boids.dir/Flock.cpp.o"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/boids.dir/Flock.cpp.o -c /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/Flock.cpp

src/CMakeFiles/boids.dir/Flock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boids.dir/Flock.cpp.i"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/Flock.cpp > CMakeFiles/boids.dir/Flock.cpp.i

src/CMakeFiles/boids.dir/Flock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boids.dir/Flock.cpp.s"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && /lusr/opt/gcc-5.2.0/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src/Flock.cpp -o CMakeFiles/boids.dir/Flock.cpp.s

src/CMakeFiles/boids.dir/Flock.cpp.o.requires:
.PHONY : src/CMakeFiles/boids.dir/Flock.cpp.o.requires

src/CMakeFiles/boids.dir/Flock.cpp.o.provides: src/CMakeFiles/boids.dir/Flock.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/boids.dir/build.make src/CMakeFiles/boids.dir/Flock.cpp.o.provides.build
.PHONY : src/CMakeFiles/boids.dir/Flock.cpp.o.provides

src/CMakeFiles/boids.dir/Flock.cpp.o.provides.build: src/CMakeFiles/boids.dir/Flock.cpp.o

# Object files for target boids
boids_OBJECTS = \
"CMakeFiles/boids.dir/procedure_geometry.cc.o" \
"CMakeFiles/boids.dir/render_pass.cc.o" \
"CMakeFiles/boids.dir/main.cc.o" \
"CMakeFiles/boids.dir/gui.cc.o" \
"CMakeFiles/boids.dir/Flock.cpp.o"

# External object files for target boids
boids_EXTERNAL_OBJECTS =

bin/boids: src/CMakeFiles/boids.dir/procedure_geometry.cc.o
bin/boids: src/CMakeFiles/boids.dir/render_pass.cc.o
bin/boids: src/CMakeFiles/boids.dir/main.cc.o
bin/boids: src/CMakeFiles/boids.dir/gui.cc.o
bin/boids: src/CMakeFiles/boids.dir/Flock.cpp.o
bin/boids: src/CMakeFiles/boids.dir/build.make
bin/boids: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/boids: libutgraphicsutil.a
bin/boids: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/boids: /usr/lib/x86_64-linux-gnu/libGL.so
bin/boids: /usr/lib/x86_64-linux-gnu/libjpeg.so
bin/boids: /usr/lib/x86_64-linux-gnu/libGL.so
bin/boids: /usr/lib/x86_64-linux-gnu/libjpeg.so
bin/boids: src/CMakeFiles/boids.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/boids"
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/boids.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/boids.dir/build: bin/boids
.PHONY : src/CMakeFiles/boids.dir/build

src/CMakeFiles/boids.dir/requires: src/CMakeFiles/boids.dir/procedure_geometry.cc.o.requires
src/CMakeFiles/boids.dir/requires: src/CMakeFiles/boids.dir/render_pass.cc.o.requires
src/CMakeFiles/boids.dir/requires: src/CMakeFiles/boids.dir/main.cc.o.requires
src/CMakeFiles/boids.dir/requires: src/CMakeFiles/boids.dir/gui.cc.o.requires
src/CMakeFiles/boids.dir/requires: src/CMakeFiles/boids.dir/Flock.cpp.o.requires
.PHONY : src/CMakeFiles/boids.dir/requires

src/CMakeFiles/boids.dir/clean:
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src && $(CMAKE_COMMAND) -P CMakeFiles/boids.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/boids.dir/clean

src/CMakeFiles/boids.dir/depend:
	cd /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /v/filer4b/v38q001/jfish7/Documents/Graphics/boids /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/src /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src /v/filer4b/v38q001/jfish7/Documents/Graphics/boids/build/src/CMakeFiles/boids.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/boids.dir/depend

