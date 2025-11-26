file(GLOB hdrs "*.h*" "../include/*.h")
file(GLOB srcs "*.cpp")

add_executable(matrix ${srcs} ${hdrs})
target_include_directories(matrix PRIVATE ${CMAKE_SOURCE_DIR}/include)
