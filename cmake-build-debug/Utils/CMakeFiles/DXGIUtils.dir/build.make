# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\qr973\CLionProjects\DXGI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

# Include any dependencies generated for this target.
include Utils\CMakeFiles\DXGIUtils.dir\depend.make

# Include the progress variables for this target.
include Utils\CMakeFiles\DXGIUtils.dir\progress.make

# Include the compile flags for this target's objects.
include Utils\CMakeFiles\DXGIUtils.dir\flags.make

Utils\CMakeFiles\DXGIUtils.dir\BmpUtils.cpp.obj: Utils\CMakeFiles\DXGIUtils.dir\flags.make
Utils\CMakeFiles\DXGIUtils.dir\BmpUtils.cpp.obj: ..\Utils\BmpUtils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Utils/CMakeFiles/DXGIUtils.dir/BmpUtils.cpp.obj"
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\Utils
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1425~1.286\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\DXGIUtils.dir\BmpUtils.cpp.obj /FdCMakeFiles\DXGIUtils.dir\ /FS -c C:\Users\qr973\CLionProjects\DXGI\Utils\BmpUtils.cpp
<<
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

Utils\CMakeFiles\DXGIUtils.dir\BmpUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DXGIUtils.dir/BmpUtils.cpp.i"
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\Utils
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1425~1.286\bin\Hostx86\x86\cl.exe > CMakeFiles\DXGIUtils.dir\BmpUtils.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\qr973\CLionProjects\DXGI\Utils\BmpUtils.cpp
<<
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

Utils\CMakeFiles\DXGIUtils.dir\BmpUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DXGIUtils.dir/BmpUtils.cpp.s"
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\Utils
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1425~1.286\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\DXGIUtils.dir\BmpUtils.cpp.s /c C:\Users\qr973\CLionProjects\DXGI\Utils\BmpUtils.cpp
<<
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

# Object files for target DXGIUtils
DXGIUtils_OBJECTS = \
"CMakeFiles\DXGIUtils.dir\BmpUtils.cpp.obj"

# External object files for target DXGIUtils
DXGIUtils_EXTERNAL_OBJECTS =

DXGIUtils.dll: Utils\CMakeFiles\DXGIUtils.dir\BmpUtils.cpp.obj
DXGIUtils.dll: Utils\CMakeFiles\DXGIUtils.dir\build.make
DXGIUtils.dll: Utils\CMakeFiles\DXGIUtils.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ..\DXGIUtils.dll"
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\Utils
	"C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E vs_link_dll --intdir=CMakeFiles\DXGIUtils.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1425~1.286\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\DXGIUtils.dir\objects1.rsp @<<
 /out:..\DXGIUtils.dll /implib:..\DXGIUtils.lib /pdb:C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\DXGIUtils.pdb /dll /version:0.0 /machine:X86 /debug /INCREMENTAL kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib  
<<
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

# Rule to build all files generated by this target.
Utils\CMakeFiles\DXGIUtils.dir\build: DXGIUtils.dll

.PHONY : Utils\CMakeFiles\DXGIUtils.dir\build

Utils\CMakeFiles\DXGIUtils.dir\clean:
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\Utils
	$(CMAKE_COMMAND) -P CMakeFiles\DXGIUtils.dir\cmake_clean.cmake
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug
.PHONY : Utils\CMakeFiles\DXGIUtils.dir\clean

Utils\CMakeFiles\DXGIUtils.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\qr973\CLionProjects\DXGI C:\Users\qr973\CLionProjects\DXGI\Utils C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\Utils C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\Utils\CMakeFiles\DXGIUtils.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Utils\CMakeFiles\DXGIUtils.dir\depend

