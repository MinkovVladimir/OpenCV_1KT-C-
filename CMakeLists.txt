cmake_minimum_required(VERSION 3.16)

project(OpenCV_KT1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(OpenCV_KT1 main.cpp)

target_include_directories(OpenCV_KT1 PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCV_KT1 PRIVATE ${OpenCV_LIBS})

include(GNUInstallDirs)
install(TARGETS OpenCV_KT1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
