cmake_minimum_required(VERSION 3.10)
project(QCLIB VERSION 1.0.0 LANGUAGES C CXX)

# Create the library
add_library(QCLIB header.cpp)

# Specify include directory
target_include_directories(QCLIB PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Set C++ standard
set_target_properties(QCLIB PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

# Optionally install
install(TARGETS QCLIB DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
