cmake_minimum_required(VERSION 3.16)

project(DataVisualisation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Find both Quick and Charts modules
find_package(Qt6 REQUIRED COMPONENTS Quick Graphs)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appDataVisualisation
    main.cpp
)

# ✅ Add QML module
qt_add_qml_module(appDataVisualisation
    URI DataVisualisation
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES dataprovider.h dataprovider.cpp
)

# ✅ Link necessary libraries
target_link_libraries(appDataVisualisation
    PRIVATE
        Qt6::Quick
        Qt6::Graphs
)

# ✅ Windows/macOS bundle setup
set_target_properties(appDataVisualisation PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS appDataVisualisation
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
