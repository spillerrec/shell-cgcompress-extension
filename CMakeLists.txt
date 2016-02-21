cmake_minimum_required(VERSION 3.0)

add_subdirectory(deps/zlib)
add_subdirectory(deps/libarchive)

set(SOURCES
	src/pugixml/pugixml.cpp
	src/CgCompressHandler.cpp
	src/ClassFactory.cpp
	src/ZipHandler.cpp
	src/dllmain.cpp
	src/Source.def
	)

add_library(shell-cgcompress-extension SHARED ${SOURCES})

include_directories(deps/libarchive/libarchive)
target_link_libraries(shell-cgcompress-extension Windowscodecs.lib)