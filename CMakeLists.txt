cmake_minimum_required(VERSION 2.8)
project(engine)

add_definitions("-g")

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -DDEBUG -D_DEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -DDEBUG -D_DEBUG")
endif(CMAKE_COMPILER_IS_GNUCXX)

#################### GLEW

find_package(GLEW REQUIRED)

if(GLEW_FOUND)
    message(STATUS "Found GLEW")
endif(GLEW_FOUND)

#################### GLFW

add_subdirectory(thirdparty/glfw-3.0.3/)

#################### assimp

find_package(ASSIMP REQUIRED)

if(ASSIMP_FOUND)
    message(STATUS "Found ASSIMP")
endif(ASSIMP_FOUND)

add_subdirectory(thirdparty/assimp/)

#################### DevIL

find_package(DevIL REQUIRED)

if(DevIL_FOUND)
    message(STATUS "Found DevIL")
endif(DevIL_FOUND)

####################

include_directories(${GLEW_INCLUDE_PATH}
    ${GLM_INCLUDE_DIRS}
    /opt/local/include
    thirdparty/glfw-3.0.3/include
    thirdparty/assimp/include)

IF(APPLE)
    SET(EXTRA_LIBS "-framework Cocoa -framework OpenGL")
ENDIF(APPLE)

set(engine_HEADER
    src/Camera.h
    src/Object.h
    src/LightSource.h
    src/Shader.h
    src/Scene.h
    src/ShaderProgram.h
    src/Error.h)

set(engine_SOURCE
    src/ILEngine.cpp
    src/Camera.cpp
    src/Engine.cpp
    src/Object.cpp
    src/LightSource.cpp
    src/ShaderProgram.cpp
    src/Shader.cpp
    src/Scene.cpp
    src/Error.cpp)

add_executable(engine
    ${engine_SOURCE}
    ${engine_HEADER})

message(STATUS ${EXTRA_LIBS})
message(STATUS ${GLEW_LIBRARY})

target_link_libraries(engine
    ${EXTRA_LIBS}
    ${GLEW_LIBRARY}
    glfw ${GLFW_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    ${ILU_LIBRARIES}
    ${IL_LIBRARIES})

####################

set(GTEST thirdparty/gtest-1.7.0/)
set(TESTS
    test/ShaderTest.cpp src/Error.cpp src/Shader.cpp src/ShaderProgram.cpp src/Object.cpp)

include_directories(${GTEST}include)
add_subdirectory(${GTEST})

add_executable(shadertest ${TESTS})

target_link_libraries(shadertest
    gtest
    ${GLEW_LIBRARY}
    glfw ${GLFW_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    ${EXTRA_LIBS}
    ${ILU_LIBRARIES}
    ${IL_LIBRARIES})

####################

enable_testing()

add_test(shader shadertest)
