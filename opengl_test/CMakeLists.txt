cmake_minimum_required(VERSION 2.8)

# VTK is required
#find_package(VTK REQUIRED)
#include(${VTK_USE_FILE})

# Boost is required
find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
  set(BOOST_ROOT "" CACHE PATH "")
endif()

add_executable(nompidl dlist.C readGL.C prep_render.C)

include_directories(${Boost_INCLUDE_DIRS})

#target_link_libraries(nompidl -lX11 -lGL -lmpi)
target_link_libraries(nompidl -lX11 -lGL -lopen-pal) #-lopen-rte)
