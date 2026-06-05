cmake_minimum_required(VERSION 3.16)
project(InventarisMBG VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Q
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/core/Algorithms.cpp
    src/core/InventoryManager.cpp
    src/core/UserManager.cpp
    src/gui/LoginDialog.cpp
    src/gui/MainWindow.cpp
)

# Headers
set(HEADERS
    include/core/BahanMakanan.h
    include/core/User.h
    include/core/Algorithms.h
    include/core/InventoryManager.h
    include/core/UserManager.h
    include/gui/LoginDialog.h
    include/gui/MainWindow.h
)

add_executable(InventarisMBG WIN32 ${SOURCES} ${HEADERS})
target_link_libraries(InventarisMBG PRIVATE Qt6::Widgets)

# Unit Test Executable
add_executable(test_algo tests/test_algorithms.cpp src/core/Algorithms.cpp)
target_include_directories(test_algo PRIVATE include)
