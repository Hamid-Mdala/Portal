cmake_minimum_required(VERSION 3.10)
project(Portal)

# Set C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# REQUIRED Qt6 components with find_package (non-negotiable)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Enable Qt's meta-object compiler (MOC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Manual MariaDB configuration (since find_package failed)
set(MARIADB_INCLUDE_DIR "/usr/include/mariadb")
set(MARIADB_LIBRARY "/usr/lib64/mariadb/libmariadb.so")

add_executable(portal
        main.cpp
        PortalUsers.cpp
        NavigationMenus.cpp
        DatabaseManager.cpp
        HandlingValidationCheck.cpp
)

# Include directories
target_include_directories(portal PRIVATE
        ${MARIADB_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(portal PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        ${MARIADB_LIBRARY}
)

# Additional linker flags for MariaDB
target_link_options(portal PRIVATE
        -Wl,--no-as-needed  # Fixes linker issues on some systems
)