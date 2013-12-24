cmake_minimum_required(VERSION 2.8)
project(engine)

add_definitions("-g")

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -DDEBUG -D_DEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -DDEBUG -D_DEBUG")
endif(CMAKE_COMPILER_IS_GNUCXX)

####################

find_package(GLEW REQUIRED)

if(GLEW_FOUND)
    message(STATUS "Found GLEW")
endif(GLEW_FOUND)

add_subdirectory(thirdparty/glfw-3.0.3/)
add_subdirectory(thirdparty/assimp/)

include_directories(${GLEW_INCLUDE_PATH}
    ${GLM_INCLUDE_DIRS}
    /opt/local/include
    thirdparty/glfw-3.0.3/include
    thirdparty/assimp/include)

IF(APPLE)
    SET(EXTRA_LIBS "-framework Cocoa -framework OpenGL")
ENDIF(APPLE)

set(engine_HEADER
    src/Model.h
    src/ModelLoader.h
    src/Object.h
    src/tiny_obj_loader.h
    src/Shader.h
    src/Vertex.h
    src/Scene.h
    src/ShaderProgram.h
    src/Error.h)

set(engine_SOURCE
    src/Engine.cpp
    src/Model.cpp
    src/ModelLoader.cpp
    src/Object.cpp
    src/ShaderProgram.cpp
    src/Shader.cpp
    #src/Vertex.cpp
    src/Scene.cpp
    src/Error.cpp
    src/tiny_obj_loader.cc)

add_executable(engine
    ${engine_SOURCE}
    ${engine_HEADER})

message(STATUS ${EXTRA_LIBS})
message(STATUS ${GLEW_LIBRARY})

target_link_libraries(engine
    ${EXTRA_LIBS}
    ${GLEW_LIBRARY}
    glfw ${GLFW_LIBRARIES})

####################

set(GTEST thirdparty/gtest-1.7.0/)
set(TESTS
    test/ModelTest.cpp src/Error.cpp src/Model.cpp)

add_subdirectory(${GTEST} ${GTEST}build/)
include_directories(${GTEST}include/)

add_executable(modeltest ${TESTS})

target_link_libraries(modeltest
    gtest
    ${EXTRA_LIBS})

####################

set(GTEST thirdparty/gtest-1.7.0/)
set(TESTS
    test/ShaderTest.cpp src/Error.cpp src/Shader.cpp src/ShaderProgram.cpp src/Model.cpp src/ModelLoader.cpp src/Object.cpp src/tiny_obj_loader.cc)

add_executable(shadertest ${TESTS})

target_link_libraries(shadertest
    gtest
    ${GLEW_LIBRARY}
    glfw ${GLFW_LIBRARIES}
    ${EXTRA_LIBS})

####################

enable_testing()

add_test(model modeltest)
add_test(shader shadertest)
