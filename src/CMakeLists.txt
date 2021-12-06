# Add Unity - testing framework
add_subdirectory(unity)

# Unit tests
add_subdirectory(tests)

# Automatically compile modules
# Note: requires "cmake .." when a module is created/deleted
file(GLOB moduleFiles "modules/*.c")
foreach(ModuleSource ${moduleFiles})
  string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" ModuleName ${ModuleSource}) # Remove path
  string(REPLACE "modules/" "" ModuleName ${ModuleName}) # Remove subfolder
  string(REPLACE ".c" "" ModuleName ${ModuleName}) # Remove extension
  add_library(${ModuleName} STATIC ${ModuleSource})
  list(APPEND Modules ${ModuleName})
endforeach(ModuleSource)

# Main
add_executable(main main.c)

# Link modules
target_link_libraries(main ${Modules})
