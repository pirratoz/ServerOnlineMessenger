cmake_minimum_required(VERSION 3.14)

project(OnlineMessenger LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)

file(GLOB SERVER_SRC "server/*.cpp")
file(GLOB SERVER_HEADERS "server/*.h")
file(GLOB SQL_SRC "sql/tables/*.cpp")
file(GLOB SQL_HEADERS "sql/tables/*.h")

set(
    SERVER_FILES
    server/serverUtils.h     server/serverUtils.cpp
    server/server.h          server/server.cpp
)

set(
    SQL_FILES
    sql/tables/user.h    sql/tables/user.cpp
    sql/tables/log.h     sql/tables/log.cpp
    sql/dto/logDto.h     sql/dto/logDto.cpp
    sql/dto/userDto.h    sql/dto/userDto.cpp
    sql/database.h       sql/database.cpp
)

set(
    UTILS_FILES
    utils/passwordUtils.h     utils/passwordUtils.cpp
)

# Добавление исполняемого файла
add_executable(OnlineMessenger
    main.cpp
    ${SERVER_FILES}
    ${SQL_FILES}
    ${UTILS_FILES}
)

target_link_libraries(
    OnlineMessenger
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Sql
)
