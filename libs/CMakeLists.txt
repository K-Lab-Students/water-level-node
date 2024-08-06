set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.22)

project(libs)

add_library(${PROJECT_NAME})

add_subdirectory(sim7000cmqtt)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/AT24Cxx/AT24Cxx_stm32_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/AT24Cxx/AT24Cxx_stm32_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sr04m/SR04MDriver.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/AT24Cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/sr04m
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC stm32cubemx)
