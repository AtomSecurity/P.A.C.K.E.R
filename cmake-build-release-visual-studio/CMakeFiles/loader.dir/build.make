# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\cmake-build-release-visual-studio

# Include any dependencies generated for this target.
include CMakeFiles\loader.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\loader.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\loader.dir\flags.make

CMakeFiles\loader.dir\loader.cpp.obj: CMakeFiles\loader.dir\flags.make
CMakeFiles\loader.dir\loader.cpp.obj: ..\loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\cmake-build-release-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/loader.dir/loader.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\loader.dir\loader.cpp.obj /FdCMakeFiles\loader.dir\ /FS -c C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\loader.cpp
<<

CMakeFiles\loader.dir\loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/loader.dir/loader.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\loader.dir\loader.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\loader.cpp
<<

CMakeFiles\loader.dir\loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/loader.dir/loader.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\loader.dir\loader.cpp.s /c C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\loader.cpp
<<

CMakeFiles\loader.dir\resources\resource.rc.res: CMakeFiles\loader.dir\flags.make
CMakeFiles\loader.dir\resources\resource.rc.res: ..\resources\resource.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\cmake-build-release-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object CMakeFiles/loader.dir/resources/resource.rc.res"
	C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) /fo CMakeFiles\loader.dir\resources\resource.rc.res C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\resources\resource.rc

# Object files for target loader
loader_OBJECTS = \
"CMakeFiles\loader.dir\loader.cpp.obj" \
"CMakeFiles\loader.dir\resources\resource.rc.res"

# External object files for target loader
loader_EXTERNAL_OBJECTS =

loader.exe: CMakeFiles\loader.dir\loader.cpp.obj
loader.exe: CMakeFiles\loader.dir\resources\resource.rc.res
loader.exe: CMakeFiles\loader.dir\build.make
loader.exe: CMakeFiles\loader.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\cmake-build-release-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable loader.exe"
	"C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\loader.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\loader.dir\objects1.rsp @<<
 /out:loader.exe /implib:loader.lib /pdb:C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\cmake-build-release-visual-studio\loader.pdb /version:0.0  /machine:X86 /INCREMENTAL:NO /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\loader.dir\build: loader.exe

.PHONY : CMakeFiles\loader.dir\build

CMakeFiles\loader.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\loader.dir\cmake_clean.cmake
.PHONY : CMakeFiles\loader.dir\clean

CMakeFiles\loader.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\cmake-build-release-visual-studio C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\cmake-build-release-visual-studio C:\Users\nabab\Documents\AtomSecurity\P.A.C.K.E.R\cmake-build-release-visual-studio\CMakeFiles\loader.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\loader.dir\depend

