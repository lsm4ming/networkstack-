cmake_minimum_required(VERSION 3.7)

project(net)
set(CMAKE_C_STANDARD 99)

# 指定libpcap路径
set(PCAP_ROOT_DIR ${CMAKE_SOURCE_DIR}/thirdparty/libpcap)

# 指定openssl路径
set(OPENSSL_ROOT_DIR ${CMAKE_SOURCE_DIR}/thirdparty/openssl)

# 包含三方依赖的头文件
include_directories(${PCAP_ROOT_DIR})
include_directories(${OPENSSL_ROOT_DIR}/include)

# 给visual studio编译器使用的宏，Enable GCC debug
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_compile_options(-g)

# 导入头文件
include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src/net/include
        ${PROJECT_SOURCE_DIR}/src/app/echo
        ${PROJECT_SOURCE_DIR}/src/plat
        ${PROJECT_SOURCE_DIR}/src/app
)

# 搜索src下面的所有源文件，生成文件列表
file(GLOB_RECURSE SOURCE_LIST "src/*.c" "src/*.h")

# 排除测试文件
list(REMOVE_ITEM SOURCE_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/app/test/main.c")

# 将源文件列表加入到工程中
add_executable(${PROJECT_NAME} main.c ${SOURCE_LIST})

add_executable(${PROJECT_NAME}-test ${CMAKE_CURRENT_SOURCE_DIR}/src/app/test/main.c ${SOURCE_LIST})

# 与一些库进行编译链接，生成最终的程序
# 针对网络的平台配置
add_definitions(-DNET_DRIVER_PCAP)    # use pcap

message(STATUS "current platform: ${CMAKE_HOST_SYSTEM_NAME}")

if (WIN32)
    add_definitions(-DSYS_PLAT_WINDOWS)
elseif (APPLE)
    add_definitions(-DSYS_PLAT_MAC)
elseif (UNIX)
    add_definitions(-DSYS_PLAT_LINUX)
endif ()

target_link_libraries(${PROJECT_NAME} ${PCAP_ROOT_DIR}/libpcap.a ${OPENSSL_ROOT_DIR}/libssl.a ${OPENSSL_ROOT_DIR}/libcrypto.a pthread)
target_link_libraries(${PROJECT_NAME}-test ${PCAP_ROOT_DIR}/libpcap.a ${OPENSSL_ROOT_DIR}/libssl.a ${OPENSSL_ROOT_DIR}/libcrypto.a pthread)