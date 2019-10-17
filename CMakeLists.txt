cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME splat)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall -Werror")

#----------------------------------------------------------------------------
# Define project sources and includes
#----------------------------------------------------------------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR})
include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cc)
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/cli.cc)

set(CMAKE_CXX_STANDARD 11)

################################
# Normal Libraries & Executables
################################
add_library(splat_lib ${SRC_FILES})
add_executable(splat ${PROJECT_SOURCE_DIR}/cli.cc)

target_link_libraries(splat splat_lib)

################################
# Testing
################################

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(BUILD_TESTS "Build all tests." OFF) # Makes boolean 'test' available.

if (BUILD_TESTS)
  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(lib/googletest-1.10.x)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  ##############
  # Unit Tests
  ##############
  add_executable(RunUnitTests ${TEST_SRC_FILES})

  target_link_libraries(RunUnitTests gtest gtest_main)
  target_link_libraries(RunUnitTests splat_lib)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable RunUnitTests to see those specific tests.
  add_test(UnitTests RunUnitTests)

endif()
