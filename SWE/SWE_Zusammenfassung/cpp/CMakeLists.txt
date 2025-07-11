cmake_minimum_required(VERSION 3.16)
project(Demo VERSION 1.0.0 LANGUAGES C CXX)

# enable virtual folders for projects if supported by the build system/IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

# set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# configure C11
set(CMAKE_C_STANDARD 11)          # request C11
set(CMAKE_C_STANDARD_REQUIRED ON) # enforce requested standard
set(CMAKE_C_EXTENSIONS OFF)       # disable compiler specific extensions

# configure C++20
set(CMAKE_CXX_STANDARD 20)          # request C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON) # enforce requested standard
set(CMAKE_CXX_EXTENSIONS OFF)       # disable compiler specific extensions

# openGl
#find_package(OpenGL REQUIRED)
#find_package(glfw3  REQUIRED)
#find_package(GLUT REQUIRED)
#find_package(wxWidgets COMPONENTS gl core base REQUIRED)
#include(${wxWidgets_USE_FILE})

# helper function to simplify definition of projects
function(target name)
   add_executable(${name} ${ARGN})

   #set required warning flags
   if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"   OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
      "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      target_compile_options(${name} PRIVATE
         -Wall                               # enable "all" warnings
         -Wextra                             # enable extra warnings
         -Wpedantic                          # enable strict conformance warnings
         -Wconversion                        # enable warnings for dangerous implicit conversions
         -Werror=vla                         # disable support for VLAs
         #-O3                                # enable level 3 optimization
         -Og                                 # enable debugging optimization
         -g                                  # enable debugging information
         -fsanitize=address,undefined,leak   # enable address, undefined behavior and memory leak sanitizers
      )
      target_link_libraries(${name} PRIVATE
         -fsanitize=address,undefined,leak   # enable address, undefined behavior and memory leak sanitizers
      )
      # openGl
      #target_link_libraries(${name} PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} GLU)   
      #target_include_directories(${project} PUBLIC "inc" ${wxWidgets_INCLUDE_DIRS})
      #target_link_libraries(${project} PUBLIC compile_flags glfw OpenGL::GL OpenGL::GLU ${wxWidgets_LIBRARIES})
   elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
      target_compile_options(${name} PRIVATE
         /W4          # enable almost all "necessary" warnings
         /permissive- # enforce strict standard compliance
         /JMC         # optimize debugging experience
         /MP          # enable parallel compilation
      )
   else()
      message(WARNING "unknown compiler, no warning flags set!")
   endif()
endfunction()

target(demo
   main.cpp
   interface.h
   baseclass.h
   derivedclass.h)
