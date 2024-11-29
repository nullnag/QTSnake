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
    GameWindow.h GameWindow.cpp
    InputHandler.h InputHandler.cpp
    main.cpp
    MainMenu.h MainMenu.cpp

    FieldDir/cell.cpp FieldDir/cell.h
    FieldDir/CellView.h FieldDir/CellView.cpp
    FieldDir/GameField.h FieldDir/GameField.cpp
    FieldDir/GameFieldView.h FieldDir/GameFieldView.cpp

    MultiplayerDir/ClientNetworkManager.h MultiplayerDir/ClientNetworkManager.cpp
    MultiplayerDir/CreateRoomDialog.h MultiplayerDir/CreateRoomDialog.cpp
    MultiplayerDir/IRequestHandler.h MultiplayerDir/IRequestHandler.cpp
    MultiplayerDir/MultiPlayerDialog.h MultiplayerDir/MultiPlayerDialog.cpp
    MultiplayerDir/MultiPlayerGame.h MultiplayerDir/MultiPlayerGame.cpp
    MultiplayerDir/MultiplayerMenu.h MultiplayerDir/MultiplayerMenu.cpp
    MultiplayerDir/RequestRouter.h MultiplayerDir/RequestRouter.cpp

    SingleplayerDir/Game.h SingleplayerDir/Game.cpp
    SingleplayerDir/GameOverDialog.h SingleplayerDir/GameOverDialog.cpp
    SingleplayerDir/gameRules.h SingleplayerDir/gameRules.cpp
    SingleplayerDir/GameSizeDialogue.h SingleplayerDir/GameSizeDialogue.cpp
    SingleplayerDir/Snake.h SingleplayerDir/Snake.cpp
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

target_link_libraries(GameWindow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

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

target_include_directories(GameWindow PRIVATE
    ${CMAKE_SOURCE_DIR}
    FieldDir
    MultiplayerDir
    SingleplayerDir
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GameWindow)
endif()
