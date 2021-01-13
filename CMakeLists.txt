cmake_minimum_required(VERSION 3.16..3.18)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/output/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/output/debug/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/output/debug/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/output/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/output/release/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/output/release/lib)

project(tic-tac-toe LANGUAGES CXX)
set(TARGET_NAME app)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics REQUIRED)

set(APP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/source/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/asset_ids.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/asset_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/board.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/board.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/square.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/square.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/utility.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/utility.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/button.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/component.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/container.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/gui/container.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/game_state.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/game_state.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/menu_state.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/menu_state.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/state.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/state.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/state_ids.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/state_stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/state_stack.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/title_state.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/states/title_state.h
)

add_executable(${TARGET_NAME} ${APP_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APP_SOURCES})

#target_include_directories(${TARGET_NAME} PRIVATE
#	${SFML_DIR}/include
#)

target_link_libraries(${TARGET_NAME} PRIVATE
    sfml-graphics
)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})
	set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
