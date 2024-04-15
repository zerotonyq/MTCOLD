cmake_minimum_required(VERSION 3.5)

project(DPP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        UI/src/main.cpp
        UI/src/mainwindow.cpp
        UI/include/mainwindow.h
        UI/UI_Module/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DPP
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            Core/include/Pockets.h
            Core/src/Pockets.cpp
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
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET DPP APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DPP SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DPP
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DPP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DPP)
endif()
set_target_properties(DPP PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
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
