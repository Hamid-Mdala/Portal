cmake_minimum_required(VERSION 3.10)
project(Portal)

add_subdirectory(MainWindow)
# Set C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# REQUIRED Qt6 components with find_package (non-negotiable)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets)

# Enable Qt's meta-object compiler (MOC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Manual MariaDB configuration (since find_package failed)
include_directories(/usr/include/mariadb)          # Headers
link_directories(/usr/lib64)                        # Library path

add_executable(portal
        main.cpp
        PortalUsers.h
        PortalUsers.cpp
        NavigationMenus.h
        NavigationMenus.cpp
        DatabaseManager.h
        DatabaseManager.cpp
        HandlingValidationCheck.h
        HandlingValidationCheck.cpp
)

# Link libraries
target_link_libraries(portal PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        mariadbcpp
)   # Link libmariadbcpp.so

# Additional linker flags for MariaDB
target_link_options(portal PRIVATE
        -Wl,--no-as-needed  # Fixes linker issues on some systems
)