cmake_minimum_required(VERSION 3.17)
project(Graphics)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/OpenGL/include/GLFW)
link_directories(src/OpenGL/lib/GLFW)

include_directories(src/OpenGL/include/GLEW)
link_directories(src/OpenGL/lib/GLEW)

include_directories(src/OpenGL/include/GL)
link_directories(src/OpenGL/lib/Freeglut)



include_directories(src/OpenGL/include/PNG)
link_directories(src/OpenGL/lib/PNG)

link_directories(src/OpenGL/lib/freetype)

include_directories(include)

add_executable(Graphics src/main.cpp src/Core/Window.cpp src/Core/Window.h src/Core/EventsHandler.cpp src/Core/EventsHandler.h src/Core/PerspectiveCamera.cpp src/Core/PerspectiveCamera.h src/Render/Shader.h src/Render/Mesh.h src/Loaders/pngLoader.cpp src/Loaders/pngLoader.h src/Core/Structures.h src/Loaders/objLoader.cpp src/Loaders/objLoader.h src/Core/ResourcesManager.cpp src/Core/ResourcesManager.h src/Lighting/DirectionalLight.cpp src/Lighting/DirectionalLight.h src/Lighting/PointLight.cpp src/Lighting/PointLight.h src/Render/Material.cpp src/Render/Material.h src/Core/Global.cpp src/Core/Global.h src/Logging/easylogging++.cc src/Logging/easylogging++.h src/Core/Controls.cpp src/Core/Controls.h src/Core/Actor.cpp src/Core/Actor.h src/UI/UIBase.cpp src/UI/UIBase.h src/UI/UIHandler.cpp src/UI/UIHandler.h src/Loaders/inipp.h src/Core/Config.cpp src/Core/Config.h src/Loaders/json.hpp src/Render/Model.h src/Render/stb_image.h src/Render/Model.cpp src/Loaders/cwalk.c src/Loaders/cwalk.h src/Render/Mesh.cpp src/Render/Shader.cpp)

set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)

target_link_libraries(Graphics glew32s.lib glu32 OpenGL32 freeglut libglfw3.a libpng.dll.a freetype.dll assimp -static-libgcc)

#add_custom_target(freeglutdll
#        COMMAND ${CMAKE_COMMAND} -E copy
#        src/OpenGL/bin/freeglut.dll ${CMAKE_BINARY_DIR}
#        )

#add_custom_target(libpng3dll
#        COMMAND ${CMAKE_COMMAND} -E copy
#        src/OpenGL/bin/libpng3.dll ${CMAKE_BINARY_DIR}
#        )

#add_dependencies(Graphics libpng3dll)
#add_dependencies(Graphics freeglutdll)
