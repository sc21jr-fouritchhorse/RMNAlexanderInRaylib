cmake_minimum_required(VERSION 3.11)
project(AlexanderInGLFW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCE_FILES "src/*")
file(GLOB HEADER_FILES "include")

# Use FetchContent if available (CMake 3.11 or later)
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.11)
    include(FetchContent)

    FetchContent_Declare(
            glfw
            GIT_REPOSITORY "https://github.com/glfw/glfw.git"
            GIT_TAG 3.3.9
    )

    FetchContent_MakeAvailable(glfw)

    FetchContent_Declare(
            glm
            GIT_REPOSITORY "git@github.com:g-truc/glm.git"
            GIT_TAG 1.0.0
    )

    FetchContent_MakeAvailable(glm)
else ()
    # If FetchContent is unavailable, consider alternative dependency management.
    message(WARNING "FetchContent is not available in CMake version " ${CMAKE_VERSION}.
            "You might need to build GLFW from source or use a third-party package manager.")
endif ()


set(TARGET_NAME AlexanderInGLFW)
add_executable(${TARGET_NAME}
        src/main.cpp
        include/ecsCoordinator.h
        include/components.h
        include/ecsCoordinator.h
        include/ECSDefs.h
        include/entity.h
        include/event.h
        include/system.h
        include/WindowSpecification.h
        include/WindowSystem.h
        src/components.cpp
        src/entity.cpp
        src/event.cpp
        src/main.cpp
        src/system.cpp
        src/WindowSystem.cpp
        src/main.cpp
        src/WindowSystem.cpp
        include/components.h
        src/components.cpp
        include/componentManager.h
        include/componentManager.h
        include/componentManager.h)

target_include_directories(AlexanderInGLFW PUBLIC ${HEADER_FILES})

target_link_libraries(${TARGET_NAME} glm glfw)

set_target_properties(${TARGET_NAME} PROPERTIES
        CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
