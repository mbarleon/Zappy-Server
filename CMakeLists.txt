cmake_minimum_required(VERSION 3.16)
project(zappy-server VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

########################################
# INFO: enable multithreading for build
########################################
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

########################################
# INFO: CMake cache management for faster builds
########################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

########################################
# NOTE: zappy-server configuration
########################################
add_subdirectory(external/lib-cextend EXCLUDE_FROM_ALL)

########################################

file(GLOB MAIN_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    set(MY_RPATH "@loader_path/libs")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(MY_RPATH "\$ORIGIN/libs")
endif()

set(CMAKE_INSTALL_RPATH "${MY_RPATH}")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

add_executable(zappy-server
    ${MAIN_SOURCE}
)

target_compile_options(zappy-server PRIVATE
    # INFO: classic warnings
    -Wall
    -Wextra
    -Werror
    -pedantic

    # INFO: type safety & conversions
    -Wconversion
    -Wsign-conversion
    -Wfloat-equal

    # INFO: code correctness
    -Wshadow
    -Wnull-dereference
    -Wundef
    -Wuninitialized
    -Winit-self
    -Wredundant-decls

    # INFO: code hygiene
    -Wcast-align
    -Wcast-qual
    -Wmissing-declarations

    # INFO: logic bugs & bad practices
    -Wswitch-default
    -Wswitch-enum

    # INFO: prevent common portability issues
    -Wdouble-promotion
    -Wwrite-strings

    # INFO: disabling this because this causes a compilation error
    -Wno-gnu-zero-variadic-macro-arguments
)

target_link_libraries(zappy-server PRIVATE cextend)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(zappy-server PRIVATE -Wno-format-truncation)
endif()

########################################

option(ENABLE_DEBUG "Enable debug definition" OFF)

if(ENABLE_DEBUG)
    target_compile_definitions(zappy-server PRIVATE ZAP_SRV_DEBUG=1)
endif()

########################################

file(GLOB TEST_SOURCE
    "tests/*.c")

add_executable(zap_srv_unit_tests
    ${TEST_SOURCE}
    ${MAIN_SOURCE}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    target_compile_options(zap_srv_unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(zap_srv_unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(zap_srv_unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_options(zap_srv_unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
endif()

target_compile_definitions(zap_srv_unit_tests PRIVATE UNIT_TESTS=1)

target_link_libraries(zap_srv_unit_tests PRIVATE criterion sfml-graphics sfml-system sfml-window, cextend)

target_include_directories(zap_srv_unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

enable_testing()
add_test(NAME zap_srv_unit_tests COMMAND zap_srv_unit_tests)

add_custom_target(zap_srv_tests_run
    COMMAND zap_srv_unit_tests
    DEPENDS zap_srv_unit_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

get_property(_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/lib-cextend PROPERTY BUILDSYSTEM_TARGETS)
message(STATUS "Targets in lib-cextend: ${_targets}")
