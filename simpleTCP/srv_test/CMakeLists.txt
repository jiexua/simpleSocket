# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.2)
# 项目信息
project (server_test)
#
if(WIN32)
    message(STATUS "windows compiling...")
    add_definitions(-D_PLATFORM_IS_WINDOWS_)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(WIN_OS true)
else(WIN32)
    message(STATUS "linux compiling...")
    add_definitions( -D_PLATFORM_IS_LINUX_)
    set(UNIX_OS true)
    set(_DEBUG true)
    
endif(WIN32)
 
#
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
 
# 指定源文件的目录,并将名称保存到变量
SET(source_h
    #
    #${PROJECT_SOURCE_DIR}/../common/pfunc_print.h
    ${PROJECT_SOURCE_DIR}/../common/queuedata.h
    #${PROJECT_SOURCE_DIR}/../common/conf.h
    ${PROJECT_SOURCE_DIR}/../common/Mutex.h
    ${PROJECT_SOURCE_DIR}/../common/hashmap.h
    ${PROJECT_SOURCE_DIR}/../common/myFunc.h
    ${PROJECT_SOURCE_DIR}/../common/Log.h
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocket.h
	${PROJECT_SOURCE_DIR}/../srv_IO/MySocketRD.h
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocketWD.h
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocketPrivate.h
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocketSrv.h
  )
  
SET(source_cpp
    #
    ${PROJECT_SOURCE_DIR}/../common/Mutex.cpp
    ${PROJECT_SOURCE_DIR}/../common/hashmap.cpp
    ${PROJECT_SOURCE_DIR}/../common/myFunc.cpp
    ${PROJECT_SOURCE_DIR}/../common/Log.cpp
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocket.cpp
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocketRD.cpp
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocketWD.cpp
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocketPrivate.cpp
    ${PROJECT_SOURCE_DIR}/../srv_IO/MySocketSrv.cpp
	${PROJECT_SOURCE_DIR}/main.cpp
  )
  
#头文件目录
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/../common
  ${PROJECT_SOURCE_DIR}/../srv_IO
  )
 
if (${UNIX_OS})
 
SET(source_h_linux
${PROJECT_SOURCE_DIR}/../common/myThread.h
)
 
SET(source_cpp_linux
  ${PROJECT_SOURCE_DIR}/../common/myThread.cpp
)
 
add_definitions(
  "-W"
  "-fPIC"
  "-Wall"
  # "-Wall -g"
#   "-Werror"
  "-Wshadow"
  "-Wformat"
  "-Wpointer-arith"
  "-D_REENTRANT"
  "-D_USE_FAST_MACRO"
  "-Wno-long-long"
  "-Wuninitialized"
  "-D_POSIX_PTHREAD_SEMANTICS"
  "-DACL_PREPARE_COMPILE"
  "-Wno-unused-parameter"
  "-fexceptions"
  )
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
 
link_directories()
# 指定生成目标
add_executable(server_test ${source_h} ${source_cpp} ${source_h_linux} ${source_cpp_linux})
#link
target_link_libraries(server_test 
  -lpthread -pthread -lz -lrt -ldl
)
 
endif(${UNIX_OS})
 
if (${WIN_OS})
 
SET(source_h_win
  ${PROJECT_SOURCE_DIR}/../common/win32Thread.h
)
 
SET(source_cpp_win
  ${PROJECT_SOURCE_DIR}/../common/win32Thread.cpp
)
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4819")
 
add_definitions(
  "-D_CRT_SECURE_NO_WARNINGS"
  "-D_WINSOCK_DEPRECATED_NO_WARNINGS"
  "-DNO_WARN_MBCS_MFC_DEPRECATION"
  "-DWIN32_LEAN_AND_MEAN"
)
 
link_directories()
 
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../bin)
# 指定生成目标
add_executable(server_testd ${source_h} ${source_cpp} ${source_h_win}  ${source_cpp_win})
 
#target_link_libraries(server_testd *.lib)
 
else(CMAKE_BUILD_TYPE)
 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin)
# 指定生成目标
add_executable(server_test ${source_h} ${source_cpp} ${source_h_win} ${source_cpp_win})
 
#target_link_libraries(server_test *.lib)
 
endif (CMAKE_BUILD_TYPE)
 
endif(${WIN_OS})