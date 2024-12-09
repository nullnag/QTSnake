cmake_minimum_required(VERSION 3.14)

project(Server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(Server
  main.cpp
  server.h server.cpp
  SessionManager.h SessionManager.cpp

  Session.h Session.cpp
  IRequestHandler.h IRequestHandler.cpp
  RequestRouter.h RequestRouter.cpp
  Snake.h Snake.cpp
  GameField.h GameField.cpp
  Cell.h Cell.cpp
  Game.h Game.cpp
  GameRules.h GameRules.cpp
)
target_link_libraries(Server PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
