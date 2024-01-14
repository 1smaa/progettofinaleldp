#LORENZON ISMAELE
cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(MyMonopolyGame)

include_directories(include)

# Create a shared library
add_library(MyMonopoly SHARED
    src/Dadi.cpp
    src/Partita.cpp
    src/Board.cpp    
    src/Player.cpp
    src/Box.cpp
)

# Add executable and specify source files
add_executable(main
    src/main.cpp
)

# Link the executable against the shared library
target_link_libraries(main PUBLIC MyMonopoly)
