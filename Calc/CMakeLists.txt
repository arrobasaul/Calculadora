# If you have source files for an executable
add_executable(Calc src/main.cpp)

# If you are using C++20 Modules:
# For module interfaces (.ixx, .cppm, etc.)
target_sources(Calc PUBLIC
    FILE_SET CXX_MODULES FILES
    modules/my_module.ixx
    modules/another_module.cppm
)

# For module implementation files (if separate)
target_sources(Calc PRIVATE
    modules/my_module_impl.cpp
)

# If you have other standard C++ source files
#target_sources(Calc PRIVATE
#    src/utility.cpp
#)

# Link libraries if needed
# target_link_libraries(MyExecutable PRIVATE MyLibrary)

# Add include directories if you have custom headers
# target_include_directories(MyExecutable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)