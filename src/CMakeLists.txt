# Add Unity - testing framework
add_subdirectory(unity)

# Unit tests
add_subdirectory(tests)

# Modules
add_library(argparser STATIC modules/argparser.c)
add_library(showhelp STATIC modules/showhelp.c)

# Main
add_executable(main main.c)

# Link modules
target_link_libraries(main argparser showhelp)

