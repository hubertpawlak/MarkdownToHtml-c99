# Add Unity - testing framework
add_subdirectory(unity)

# Unit tests
add_subdirectory(tests)

# Modules
add_library(argparser modules/argparser)

# Main
add_executable(main main.c)

# Link modules
target_link_libraries(main argparser)

