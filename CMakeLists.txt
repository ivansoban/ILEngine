cmake_minimum_required(VERSION 2.8)

project(engine)

add_executable(modeltest _model.cpp _model_loader.cpp _object.cpp include/tinyobjloader/tiny_obj_loader.cc)

include_directories(/opt/local/lib /opt/local/include)

target_link_libraries(modeltest ${OPENGL_LIBRARIES} glfw)
