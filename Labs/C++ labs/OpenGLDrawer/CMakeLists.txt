cmake_minimum_required(VERSION 3.17)
project(Graphics)

set(CMAKE_CXX_STANDARD 14)

include_directories(include/OpenGL/include/GLFW)
link_directories(include/OpenGL/lib/GLFW)

include_directories(include/OpenGL/include/GLEW)
link_directories(include/OpenGL/lib/GLEW)

include_directories(include)

add_executable(Graphics src/main.cpp src/Core/Window.cpp src/Core/Window.h src/Core/EventsHandler.cpp src/Core/EventsHandler.h src/Core/PerspectiveCamera.cpp src/Core/PerspectiveCamera.h src/Render/Shader.h src/Render/Mesh.h src/Core/Structures.h src/Core/ResourcesManager.cpp src/Core/ResourcesManager.h src/Lighting/DirectionalLight.cpp src/Lighting/DirectionalLight.h src/Lighting/PointLight.cpp src/Lighting/PointLight.h src/Core/Global.cpp src/Core/Global.h src/Logging/easylogging++.cc src/Logging/easylogging++.h src/Core/Actor.cpp src/Core/Actor.h src/UI/UIBase.cpp src/UI/UIBase.h src/UI/UIHandler.cpp src/UI/UIHandler.h src/Loaders/inipp.h src/Core/Config.cpp src/Core/Config.h src/Loaders/json.hpp src/Render/Model.h src/Render/stb_image.h src/Render/Model.cpp src/Loaders/cwalk.c src/Loaders/cwalk.h src/Render/Mesh.cpp src/Render/Shader.cpp src/Core/InGameException.cpp src/Core/InGameException.h src/Core/Application.cpp src/Core/Application.h)

set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)

target_link_libraries(Graphics glew32s.lib OpenGL32.lib libglfw3.a freetype.lib assimp.lib)
