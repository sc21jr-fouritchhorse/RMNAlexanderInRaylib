cmake_minimum_required(VERSION 3.12)
project(AlexanderInGLFW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8  # Replace with desired version
)
FetchContent_MakeAvailable(glm)

file(GLOB SOURCE_FILES "**/*.cpp")
file(GLOB HEADER_FILES "**/*.h")
file(GLOB EXTERNAL_SRC "deps/**/*.cpp")
file(GLOB EXTERNAL_INC "deps/**/*.h")

set(TARGET_NAME AlexanderInGLFW)
add_executable(${TARGET_NAME} ${EXTERNAL_SRC} ${SOURCE_FILES}
        WormApp/Data/WindowSpecification.h
        WormApp/Systems/WindowSystem.cpp)
target_include_directories(${TARGET_NAME} PUBLIC ${EXTERNAL_INC})
target_include_directories(${TARGET_NAME} PUBLIC ${HEADER_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES
        CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

