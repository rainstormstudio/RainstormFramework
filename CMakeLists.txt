cmake_minimum_required(VERSION 3.9)

project(REngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(THREADS_PREFER_PTHREAD_FLAG ON)

cmake_policy(SET CMP0072 NEW)

if(UNIX)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glm REQUIRED)
    find_package(Threads REQUIRED)
    include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
    )
endif()

file(GLOB_RECURSE SRC_CPP_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.h")

add_executable(
    ${PROJECT_NAME}
    ${SRC_CPP_FILES}
    ${HEADER_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC "${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}"
)

if(UNIX)
    target_link_libraries(
        ${PROJECT_NAME}
        OpenGL::GL
        ${GLEW_LIBRARIES}
        glfw
        Threads::Threads
    )
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

