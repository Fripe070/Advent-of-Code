cmake_minimum_required(VERSION 3.11)
project(AoC)
set(CMAKE_CXX_STANDARD 23)

add_executable(AoC main.cpp)

include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e#refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)
target_link_libraries(AoC PRIVATE glm::glm)
