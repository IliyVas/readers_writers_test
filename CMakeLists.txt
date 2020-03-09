cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME readers_writers)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

MACRO(COPY_FILE_IF_CHANGED in_file out_file target)
    IF (${in_file} IS_NEWER_THAN ${out_file})
        message("Copying file: ${in_file} to: ${out_file}")
        ADD_CUSTOM_COMMAND(
                TARGET ${target}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND}
                ARGS -E copy ${in_file} ${out_file}
        )
    ENDIF (${in_file} IS_NEWER_THAN ${out_file})
ENDMACRO(COPY_FILE_IF_CHANGED)

SET(CPP_FILES
        src/main.cpp
        src/model/ColorSquareMatrix.cpp
        src/model/Color.cpp
        src/model/TrickySquarePainter.cpp
        src/model/PaintWriter.cpp
        src/model/PaintReader.cpp
        src/gui/SimpleWindow.cpp)

IF (WIN32)
    SET(CPP_FILES ${CPP_FILES} src/threads/win_threads.cpp)
ELSE ()
    message(FATAL_ERROR "Windows required")
ENDIF ()

set(SFML_STATIC_LIBRARIES TRUE)
IF ((${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU") AND (${CMAKE_SIZEOF_VOID_P} EQUAL 8))
    set(SFML_DIR "lib/SFML-2.5.1/mingw_x64/lib/cmake/SFML")
ELSE ()
    message(FATAL_ERROR "You should use mingw_x64 or compile SFML and set SFML_DIR variable yourself")
ENDIF ()
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

COPY_FILE_IF_CHANGED(${CMAKE_CURRENT_SOURCE_DIR}/resources/OpenSans.ttf ${CMAKE_BINARY_DIR}/OpenSans.ttf ${PROJECT_NAME})