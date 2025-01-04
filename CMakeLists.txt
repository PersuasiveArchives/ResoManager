# CMakeLists.txt for a cross-platform project (Qt and GTK)

cmake_minimum_required(VERSION 3.10)
project(ResoManager)

# Set the source files that are common across platforms
set(SOURCES
    src/display_manager.cpp
)

# Platform-specific settings
if (UNIX AND NOT APPLE)
    # Linux platform: Use GTK
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

    set(SOURCES ${SOURCES} 
        src/gui_gtk.cpp
    )

    message(STATUS "Building for Linux with GTK")

    # Create the executable and link GTK
    add_executable(resomanager ${SOURCES})
    target_include_directories(resomanager PRIVATE ${GTK3_INCLUDE_DIRS})
    target_link_libraries(resomanager PRIVATE ${GTK3_LIBRARIES})

elseif (APPLE)
    # macOS platform: Use Qt
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

    set(SOURCES ${SOURCES} 
        src/gui_qt.cpp
    )

    message(STATUS "Building for macOS with Qt")

    # Create the executable and link Qt
    add_executable(resomanager ${SOURCES})
    target_link_libraries(resomanager Qt5::Core Qt5::Widgets)

elseif (WIN32)
    # Windows platform: Use Qt
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

    set(SOURCES ${SOURCES} 
        src/gui_qt.cpp
    )

    message(STATUS "Building for Windows with Qt")

    # Create the executable and link Qt
    add_executable(resomanager ${SOURCES})
    target_link_libraries(resomanager Qt5::Core Qt5::Widgets)

else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Include directories for source files
target_include_directories(resomanager PRIVATE ${CMAKE_SOURCE_DIR}/src)
