SET(pwd ${CMAKE_CURRENT_LIST_DIR})

SET(src "")
AUX_SOURCE_DIRECTORY(${pwd} src)
add_executable(boids ${src})
message(STATUS "boids added ${src}")

target_link_libraries(boids ${stdgl_libraries})
FIND_PACKAGE(JPEG REQUIRED)
TARGET_LINK_LIBRARIES(boids ${JPEG_LIBRARIES})
