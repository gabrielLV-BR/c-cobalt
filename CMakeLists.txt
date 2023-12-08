cmake_minimum_required(VERSION 3.17)

project(cobalt)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.c" "src/**/*.c")

set(MODULES "${CMAKE_SOURCE_DIR}/modules")
set(VENDOR "${CMAKE_SOURCE_DIR}/vendor")

add_subdirectory("${MODULES}/glfw")
add_subdirectory("${MODULES}/glad/cmake")

# create glad lib

glad_add_library(glad SHARED API gl:core=4.0 LOCATION "${VENDOR}/glad/")

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} glfw glad)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    "src/"
    "${MODULES}/"
    "${MODULES}/glfw/include/"
    "${VENDOR}/glad/include/"
)
