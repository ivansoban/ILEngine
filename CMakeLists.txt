cmake_minimum_required(VERSION 2.8)
project(engine)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -DDEBUG -D_DEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -DDEBUG -D_DEBUG")
endif(CMAKE_COMPILER_IS_GNUCXX)

####################

find_package(GLFW REQUIRED)

if(GLFW_FOUND)
    message(STATUS "Found GLFW")
endif(GLFW_FOUND)

find_package(GLEW REQUIRED)

add_definitions(${GLFW_CFLAGS_OTHER})

include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH})

link_directories(${GLFW_LIBRARY_DIRS})

IF(APPLE)
    SET(EXTRA_LIBS "-framework Cocoa -framework OpenGL")
ELSE(APPLE)
    SET(EXTRA_LIBS ${GLFW_LDFLAGS_OTHER})
ENDIF(APPLE)

set(engine_HEADER
    _model.h
    _model_loader.h
    _object.h
    _primitive.h
    tiny_obj_loader.h)

set(engine_SOURCE
    _model.cpp
    _model_loader.cpp
    _object.cpp
    tiny_obj_loader.cc)

add_executable(engine
    ${engine_SOURCE}
    ${engine_HEADER})

message(STATUS ${EXTRA_LIBS})
message(STATUS ${GLEW_LIBRARY})
message(STATUS ${GLFW_LIBRARIES})

target_link_libraries(engine
    ${GLFW_LIBRARIES}
    ${EXTRA_LIBS}
    ${GLEW_LIBRARY}
    )
