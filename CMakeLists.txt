cmake_minimum_required(VERSION 3.7)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(LearningBiology VERSION 1.0 DESCRIPTION "Learning Biology with code" LANGUAGES CXX)

#adding the library
add_subdirectory( src )
#Enable testing
enable_testing()

#Fix windows 
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
set(gtest_force_shared_crt ON)

FetchContent_MakeAvailable(googletest)


set( INC_FILES
    pch.h
)

set( SRC_FILES 
    pch.cpp
	test.cpp
)

add_executable( LearningBiology ${INC_FILES} ${SRC_FILES} )
target_link_libraries( LearningBiology PUBLIC gtest gtest_main )
gtest_discover_tests( LearningBiology )
target_link_libraries( LearningBiology PUBLIC BiologyFiles )


set_target_properties(
    gmock
    gmock_main
    gtest
    gtest_main
    PROPERTIES FOLDER gtest
)
set_property(DIRECTORY 
${CMAKE_CURRENT_SOURCE_DIR} 
PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})