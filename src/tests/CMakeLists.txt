# Tell the compiler where is "unity.h"
include_directories(../unity/src)

# Automatically create tests for CTest
# Note: requires "cmake .." every time the list of files changes

file(GLOB ArgParserTests "test_argparser_*.c")
foreach(TestSource ${ArgParserTests})
  string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" TestName ${TestSource}) # Remove path
  string(REPLACE ".c" "" TestName ${TestName}) # Remove extension
  add_executable("${TestName}" "${TestSource}")
  target_link_libraries("${TestName}" argparser unity)
  add_test(NAME "${TestName}" COMMAND "${TestName}")
endforeach(TestSource)
