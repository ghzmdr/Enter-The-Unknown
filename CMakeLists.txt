cmake_minimum_required(VERSION 3.1)
project(Enter_The_Unknown)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/Components/GraphicsComponent.cpp
    src/Components/PhysicsComponent.cpp
    src/Components/MovementComponent.cpp
    src/Components/PlayerInputMovementComponent.cpp

    src/json/json_writer.cpp
    src/json/json_tool.h
    src/json/json_value.cpp
    src/json/json_valueiterator.inl
    src/json/json_reader.cpp
    src/Editor/FloorEditor.cpp
    src/Entities/Entity.cpp
    src/GUI/Button.cpp
    src/GUI/Component.cpp
    src/Entities/Obstacle.cpp
    src/States/FloorEditorState.cpp
    src/States/GameState.cpp
    src/States/State.cpp
    src/States/StateStack.cpp
    src/States/TitleState.cpp
    src/Loaders/EntityLoader.cpp
    src/Loaders/FloorLoader.cpp
    src/Utils/JsonParser.cpp
    src/Application.cpp
    src/Floor.cpp
    src/TileMap.cpp
    src/World.cpp
    main.cpp)

LINK_DIRECTORIES(/usr/include/SFML)
LINK_LIBRARIES(sfml-graphics sfml-window sfml-system)
include_directories(include)

add_executable(Enter_The_Unknown ${HEADER_FILES} ${SOURCE_FILES})