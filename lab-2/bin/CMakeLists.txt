add_executable(${PROJECT_NAME} main.cpp
        ../lib/number.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE number)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
