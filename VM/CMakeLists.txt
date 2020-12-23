cmake_minimum_required(VERSION 3.10)
project(VM)

set(CMAKE_CXX_STANDARD 11)

add_executable(VM main.cpp RigidBody/RigidBody.cpp RigidBody/RigidBody.h Quaternion/Quaternion.cpp Quaternion/Quaternion.h Triple/Triple.cpp Triple/Triple.h Matrix/Matrix.cpp Matrix/Matrix.h)
target_link_libraries(VM -lOpenGL32 -lfreeGLUT -lGLU32)