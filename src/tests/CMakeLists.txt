include_directories(../unity/src)

add_executable(test_argparser test_argparser.c)
target_link_libraries(test_argparser argparser unity)
add_test(NAME test_argparser COMMAND test_argparser)
