cmake_minimum_required (VERSION 2.8)
enable_language(C)

project(MakiseSDL C)

#USER CUSTOM SETTINGS
set(OPT "-O0")
set(USER_LINKER_FLAGS "-u _printf_float")
set(USER_CFLAGS "")

#You cam add your own defenitions
add_definitions(-DIS_STM32=1)

#Libraries
# includes cmake/FindSDL2.cmake
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

set(USER_INCLUDES ${SDL2_INCLUDE_DIRS})
#generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
#USER END

#CMAKE


#find and add all headers & sources & asm to target
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

#HEADERS
header_directories(INC)
include_directories(${INC} ${USER_INCLUDES})

#SOURCES
file(GLOB_RECURSE SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)
string(REGEX REPLACE "[^;]*CMakeFiles/[^;]+;?" "" SRC "${SRC}")


#list all files
message("INCLUDES:")
set(incs "")
foreach(f ${INC})
  set(incs "${incs} -I${f}")
  message(${f})
endforeach()
message("SOURCES: ")
foreach(f ${SRC})
  message(${f})
endforeach()
message("DEFINITIONS: ")
foreach(def ${PRJ_DEFS})
  message(${def})
  add_definitions("${def}")
endforeach()

#setup flags
#set(CMAKE_C_FLAGS "${PRJ_CFLAGS} ${OPT} -Wall -fdata-sections -ffunction-sections -std=c99 -g -gdwarf-2 ${USER_CFLAGS} ${CMAKE_C_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")

SET(TARGET ${CMAKE_PROJECT_NAME})

#.elf
add_executable(${TARGET} ${SRC} ${asm_SRC})
TARGET_LINK_LIBRARIES(${TARGET} ${SDL2_LIBRARIES})
