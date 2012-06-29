cmake_minimum_required(VERSION 2.8)

# VTK is required
#find_package(VTK REQUIRED)
#include(${VTK_USE_FILE})

# Boost is required
find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
  set(BOOST_ROOT "" CACHE PATH "")
endif()

add_executable(gl_test dlist.C readGL.C prep_render.C)
add_executable(gl_test_mpi dlist.C readGL.C prep_render.C)

include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(gl_test -lX11 -lGL)
target_link_libraries(gl_test_mpi -lX11 -lGL -lopen-pal)
