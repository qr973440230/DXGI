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
include ImageCapture\CMakeFiles\DXGIImageCapture.dir\depend.make

# Include the progress variables for this target.
include ImageCapture\CMakeFiles\DXGIImageCapture.dir\progress.make

# Include the compile flags for this target's objects.
include ImageCapture\CMakeFiles\DXGIImageCapture.dir\flags.make

ImageCapture\CMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.obj: ImageCapture\CMakeFiles\DXGIImageCapture.dir\flags.make
ImageCapture\CMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.obj: ..\ImageCapture\ImageCapture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ImageCapture/CMakeFiles/DXGIImageCapture.dir/ImageCapture.cpp.obj"
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\ImageCapture
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1425~1.286\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.obj /FdCMakeFiles\DXGIImageCapture.dir\ /FS -c C:\Users\qr973\CLionProjects\DXGI\ImageCapture\ImageCapture.cpp
<<
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

ImageCapture\CMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DXGIImageCapture.dir/ImageCapture.cpp.i"
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\ImageCapture
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1425~1.286\bin\Hostx86\x86\cl.exe > CMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\qr973\CLionProjects\DXGI\ImageCapture\ImageCapture.cpp
<<
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

ImageCapture\CMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DXGIImageCapture.dir/ImageCapture.cpp.s"
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\ImageCapture
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1425~1.286\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.s /c C:\Users\qr973\CLionProjects\DXGI\ImageCapture\ImageCapture.cpp
<<
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

# Object files for target DXGIImageCapture
DXGIImageCapture_OBJECTS = \
"CMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.obj"

# External object files for target DXGIImageCapture
DXGIImageCapture_EXTERNAL_OBJECTS =

DXGIImageCapture.dll: ImageCapture\CMakeFiles\DXGIImageCapture.dir\ImageCapture.cpp.obj
DXGIImageCapture.dll: ImageCapture\CMakeFiles\DXGIImageCapture.dir\build.make
DXGIImageCapture.dll: ImageCapture\CMakeFiles\DXGIImageCapture.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ..\DXGIImageCapture.dll"
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\ImageCapture
	"C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E vs_link_dll --intdir=CMakeFiles\DXGIImageCapture.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1425~1.286\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\DXGIImageCapture.dir\objects1.rsp @<<
 /out:..\DXGIImageCapture.dll /implib:..\DXGIImageCapture.lib /pdb:C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\DXGIImageCapture.pdb /dll /version:0.0 /machine:X86 /debug /INCREMENTAL d3d11.lib dxgi.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib  
<<
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug

# Rule to build all files generated by this target.
ImageCapture\CMakeFiles\DXGIImageCapture.dir\build: DXGIImageCapture.dll

.PHONY : ImageCapture\CMakeFiles\DXGIImageCapture.dir\build

ImageCapture\CMakeFiles\DXGIImageCapture.dir\clean:
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\ImageCapture
	$(CMAKE_COMMAND) -P CMakeFiles\DXGIImageCapture.dir\cmake_clean.cmake
	cd C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug
.PHONY : ImageCapture\CMakeFiles\DXGIImageCapture.dir\clean

ImageCapture\CMakeFiles\DXGIImageCapture.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\qr973\CLionProjects\DXGI C:\Users\qr973\CLionProjects\DXGI\ImageCapture C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\ImageCapture C:\Users\qr973\CLionProjects\DXGI\cmake-build-debug\ImageCapture\CMakeFiles\DXGIImageCapture.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : ImageCapture\CMakeFiles\DXGIImageCapture.dir\depend
