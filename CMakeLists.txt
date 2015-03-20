cmake_minimum_required(VERSION 3.1)
project(Enter_The_Unknown)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/Editor/FloorEditor.cpp
    src/Entities/Enemy.cpp
    src/Entities/Entity.cpp
    src/GUI/Button.cpp
    src/GUI/Component.cpp
    src/States/FloorEditorState.cpp
    src/States/GameState.cpp
    src/States/State.cpp
    src/States/StateStack.cpp
    src/States/TitleState.cpp
    src/Utils/EntityLoader.cpp
    src/Utils/FloorLoader.cpp
    src/Utils/JsonParser.cpp
    src/Application.cpp
    src/Floor.cpp
    src/TileMap.cpp
    src/GameObject.cpp
    src/Player.cpp
    src/World.cpp
    main.cpp)

LINK_DIRECTORIES(/usr/include/SFML)
LINK_DIRECTORIES(/usr/include/json)
LINK_LIBRARIES(sfml-graphics sfml-window sfml-system jsoncpp)
include_directories(include)

add_executable(Enter_The_Unknown ${HEADER_FILES} ${SOURCE_FILES})