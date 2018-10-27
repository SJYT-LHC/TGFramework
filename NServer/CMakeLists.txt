cmake_minimum_required(VERSION 3.2)
PROJECT(ServerEngine)

#包含头文件
#set(usrInc )
#set(sysInc )
#INCLUDE_DIRECTORIES(AFTER ${sysInc} ${usrInc})

#库路径
#set(sysLibPath usr/lib64 lib64/ /usr/lib64/mysql /usr/local/lib)
#set(usrLibPath  )
#LINK_DIRECTORIES(${sysLibPath} ${usrLibPath})


#包含库
#set(sysLib )
#set(usrLib )
#LINK_LIBRARIES(${sysLib} ${usrLib})

SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
#include_directories(./include)
AUX_SOURCE_DIRECTORY(CommFuc SRC)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated  -Werror -Wall ")

add_library(ServerEngine STATIC ${SRC})