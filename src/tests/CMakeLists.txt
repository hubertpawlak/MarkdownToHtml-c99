# Tell the compiler where is "unity.h"
include_directories(../unity/src)

# Semi-automatically create tests for CTest
# Note: requires "cmake .." every time a test file is created/deleted
function(easyTest TestFilesPattern LinkModules)
  message(STATUS "Generating tests for: ${TestFilesPattern}")
  file(GLOB TestFiles ${TestFilesPattern})
  foreach(TestSource ${TestFiles})
    string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" TestName ${TestSource}) # Remove path
    string(REPLACE ".c" "" TestName ${TestName}) # Remove extension
    add_executable("${TestName}" "${TestSource}") # Compile test binary
    target_link_libraries("${TestName}" ${LinkModules} unity) # Always include unit testing framework
    add_test(NAME "${TestName}" COMMAND "${TestName}") # Add test to CTest
  endforeach(TestSource)
endfunction()

easyTest("test_argparser_*.c" "argparser")
easyTest("test_conv_*.c" "conv;exclusivetag;tohtml;tohtml_h;tohtml_br;tohtml_bius;tohtml_imglink;tomd")
easyTest("test_fileexists_*.c" "fileexists")
easyTest("test_showhelp_*.c" "showhelp")
