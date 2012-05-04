PROJECT (vtk_test)
cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(level2_vtk level2_vtk.cpp)
TARGET_LINK_LIBRARIES(level2_vtk vtkRenderingOpenGL vtkIOCore vtkRenderingFreeTypeOpenGL vtkInteractionStyle)
#TARGET_LINK_LIBRARIES(level2_vtk vtkParallel)

