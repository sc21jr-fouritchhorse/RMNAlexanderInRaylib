cmake_minimum_required(VERSION 3.12)
project(GLAlexander)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# Find GLAD
set(${GLAD_INCLUDE_DIRS} "deps/glad")
include_directories(${GLAD_INCLUDE_DIRS})

# Find glm
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})


add_library(GLAD "deps/glad/glad.c")

# Add executable
add_executable(GLAlexander
    ECS/ecsDefinitions.h
    ECS/Core/ComponentArray.h
    ECS/Core/ComponentArray.cpp
    ECS/Managers/ComponentManager.h
    ECS/Managers/ComponentManager.cpp
    ECS/Core/System.h 
    ECS/Core/System.cpp
    ECS/Managers/SystemManager.h
    ECS/Managers/SystemManager.cpp
    ECS/coordinator.h
    Simulation/Components/WindowData.h
    Simulation/Systems/WindowSystem.h
    Simulation/Systems/RenderSystem.h
    Simulation/Systems/InputSystem.h
    Simulation/Components/Bone.h
    Simulation/Systems/KinematicsSystem.h
    main.cpp)

# Link libraries
target_link_libraries(GLAlexander glfw3 glm)
