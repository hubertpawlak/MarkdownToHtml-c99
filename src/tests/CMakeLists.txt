# Tell the compiler where is "unity.h"
include_directories(../unity/src)

# Automatically create tests for CTest
# Note: requires "cmake .." every time a test file is created/deleted

file(GLOB ArgParserTests "test_argparser_*.c")
foreach(TestSource ${ArgParserTests})
  string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" TestName ${TestSource}) # Remove path
  string(REPLACE ".c" "" TestName ${TestName}) # Remove extension
  add_executable("${TestName}" "${TestSource}")
  target_link_libraries("${TestName}" argparser unity)
  add_test(NAME "${TestName}" COMMAND "${TestName}")
endforeach(TestSource)

file(GLOB ShowHelpTests "test_showhelp_*.c")
foreach(TestSource ${ShowHelpTests})
string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" TestName ${TestSource}) # Remove path
string(REPLACE ".c" "" TestName ${TestName}) # Remove extension
add_executable("${TestName}" "${TestSource}")
target_link_libraries("${TestName}" showhelp unity)
add_test(NAME "${TestName}" COMMAND "${TestName}")
endforeach(TestSource)

file(GLOB convTests "test_conv_*.c")
foreach(TestSource ${convTests})
  string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" TestName ${TestSource}) # Remove path
  string(REPLACE ".c" "" TestName ${TestName}) # Remove extension
  add_executable("${TestName}" "${TestSource}")
  target_link_libraries("${TestName}" conv unity)
  add_test(NAME "${TestName}" COMMAND "${TestName}")
endforeach(TestSource)
