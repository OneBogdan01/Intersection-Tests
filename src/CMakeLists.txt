cmake_minimum_required(VERSION 3.7)


project(BiologyFiles VERSION 1.0 DESCRIPTION "Learning Biology with code" LANGUAGES CXX)
#Fix for windows builds
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

set( INC_FILES
	Cell.hpp

)

set( SRC_FILES 
    Cell.cpp
)
set (ALL_FILES ${INC_FILES} ${SRC_FILES})

add_library (BiologyFiles STATIC ${ALL_FILES})

target_include_directories(BiologyFiles
    PUBLIC ./    
)
