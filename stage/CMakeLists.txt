cmake_minimum_required(VERSION 3.5)

project(DPP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        UI/src/mainwindow.cpp
        UI/include/mainwindow.h
        UI/UI_Module/mainwindow.ui
        UI/src/main.cpp
        Core/include/Packets.h
        Core/src/Packets.cpp
        UI/include/indicator.h UI/src/indicator.cpp UI/UI_Module/indicator.ui
        Core/include/core.h Core/src/core.cpp
        Core/include/TestServer.h
        UI/resources.qrc
        UI/include/restart.h UI/src/restart.cpp UI/UI_Module/restart.ui
        UI/include/errorwindow.h UI/src/errorwindow.cpp UI/UI_Module/errorwindow.ui
        UI/include/indicatormanager.h
        UI/src/indicatormanager.cpp
        UI/include/indicatorwidget.h UI/src/indicatorwidget.cpp UI/UI_Module/indicatorwidget.ui
        UI/include/macaddress.h UI/src/macaddress.cpp UI/UI_Module/macaddress.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DPP
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(DPP SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(DPP
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DPP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(DPP PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DPP
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DPP)
endif()
