
# our exe name
project (paledit)

cmake_minimum_required (VERSION 2.6)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
#include_directories(${GLFW_INCLUDE_DIRS})

find_package (OpenGL REQUIRED)
find_package (PNG REQUIRED)

set(Boost_USE_SYSTEM ON)
find_package (Boost COMPONENTS filesystem system regex REQUIRED)

# source files. sure, there's a better way of doing this
set(SRC
  src/application.cc
  src/color-grid.cc
  src/font.cc
  src/main.cc
  src/mode-base.cc
  src/surface.cc
  src/video.cc
  src/palette.cc
  src/edit-color.cc
  src/new-grid-mode.cc
  src/global.cc
  src/open-file-mode.cc
  src/directory.cc
  src/save-file-mode.cc
)


link_libraries(
  #${PTHREAD_LIBRARY}
  ${Boost_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLFW_LIBRARIES}
  ${PNG_LIBRARY}
  ${ZLIB_LIBRARY}
)

add_executable(paledit ${SRC} )

add_custom_command(TARGET paledit POST_BUILD 
  COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/data COMMENT "removing stale data directory"
  COMMAND ln -sf ${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data COMMENT "linking data directory"
)
