cmake_minimum_required(VERSION 3.5)

project(GameWindow VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

set(PROJECT_SOURCES
        main.cpp
        GameWindow.cpp
        GameWindow.h
        cell.h
        cell.cpp
        Game.h
        Game.cpp
        GameField.h
        GameField.cpp
        gameRules.h
        gameRules.cpp
        Snake.h
        Snake.cpp
        GameOverDialog.h
        GameOverDialog.cpp
        MainMenu.h
        MainMenu.cpp
        GameSizeDialogue.h
        GameSizeDialogue.cpp
        CellView.h
        CellView.cpp
        GameFieldView.h
        GameFieldView.cpp
        InputHandler.h
        InputHandler.cpp
        ClientNetworkManager.h
        ClientNetworkManager.cpp
        MultiPlayerDialog.h
        MultiPlayerDialog.cpp
        MultiplayerMenu.h
        MultiplayerMenu.cpp
        RequestRouter.h
        RequestRouter.cpp
        IRequestHandler.h
        IRequestHandler.cpp
        CreateRoomDialog.h
        CreateRoomDialog.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GameWindow
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GameWindow APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GameWindow SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GameWindow
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GameWindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GameWindow PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GameWindow)
endif()
set_target_properties(GameWindow PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GameWindow
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GameWindow)
endif()
