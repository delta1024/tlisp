cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(tlisp
   VERSION 0.0.1
   LANGUAGES C
   DESCRIPTION "A tiny lisp for embeding"
)
option(BUILD_TESTS "build language tests" ON)

if (BUILD_TESTS)
   enable_testing()
endif()

add_library(${PROJECT_NAME} SHARED)
target_include_directories(${PROJECT_NAME}
        PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
file(GLOB_RECURSE PROJECT_INSTALL_HEADERS include/*.h)
target_sources(${PROJECT_NAME}
   PUBLIC FILE_SET HEADERS
   BASE_DIRS include
   FILES 
   ${PROJECT_INSTALL_HEADERS}
)
if (BUILD_TESTS)
   add_subdirectory(deps/unity)
endif()
add_subdirectory(src/lib)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   FILE_SET HEADERS
)
