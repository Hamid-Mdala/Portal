cmake_minimum_required(VERSION 3.10)
project(Portal)

# Set C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Manual MariaDB configuration (since find_package failed)
include_directories(/usr/include/mariadb)          # Headers
link_directories(/usr/lib64)                        # Library path

add_executable(Portal
        main.cpp
        ModifyPortalUsers.h
        ModifyPortalUsers.cpp
        HandleMenus.h
        HandleMenus.cpp
        DatabaseManager.h
        DatabaseManager.cpp
        HandlingValidationCheck.h
        HandlingValidationCheck.cpp
        UtililtyHandler.cpp
        UtililtyHandler.h
)

# Link libraries
target_link_libraries(Portal PRIVATE
        mariadbcpp
)   # Link libmariadbcpp.so

# Additional linker flags for MariaDB
target_link_options(Portal PRIVATE
        -Wl,--no-as-needed  # Fixes linker issues on some systems
)