project(KidsUni)
cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 17)
find_package(Qt5 COMPONENTS Core Widgets OpenGL Multimedia REQUIRED)
#find_package()

FILE(GLOB_RECURSE HEADER_FILES
    "src/*.h"
)

FILE(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "main.cpp"
)

FILE(GLOB_RECURSE CONFIG_FILES
    "ConfigFiles/*.txt"
)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${CONFIG_FILES} )
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::OpenGL Qt5::Multimedia "-pthread")

