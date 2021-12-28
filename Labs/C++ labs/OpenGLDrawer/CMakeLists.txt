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

include_directories(include)

add_executable(Graphics src/main.cpp src/general/Window.cpp src/general/Window.h src/general/EventsHandler.cpp src/general/EventsHandler.h src/general/EventsHandlerFields.h src/general/Camera.cpp src/general/Camera.h src/draw/Shader.cpp src/draw/Shader.h src/draw/Mesh.cpp src/draw/Mesh.h src/draw/Texture.cpp src/draw/Texture.h src/loaders/pngLoader.cpp src/loaders/pngLoader.h src/general/Structures.h src/loaders/objLoader.cpp src/loaders/objLoader.h src/general/ThreadSafeQueue.cpp src/general/ThreadSafeQueue.h src/general/ThreadSafeQueueFields.h)

set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)

target_link_libraries(Graphics glew32s.lib glu32 OpenGL32 freeglut libglfw3.a libpng.dll.a)
#
#add_custom_target(freeglutdll
#        COMMAND ${CMAKE_COMMAND} -E copy
#        src/OpenGL/bin/freeglut.dll ${CMAKE_BINARY_DIR}
#        )
#
#add_custom_target(glew32dll
#        COMMAND ${CMAKE_COMMAND} -E copy
#        src/OpenGL/bin/glew32.dll ${CMAKE_BINARY_DIR}
#        )
#
#add_custom_target(glfw3dll
#        COMMAND ${CMAKE_COMMAND} -E copy
#        src/OpenGL/bin/glfw3.dll ${CMAKE_BINARY_DIR}
#        )
#
#add_dependencies(Graphics glew32dll)
#add_dependencies(Graphics freeglutdll)
#add_dependencies(Graphics glfw3dll)