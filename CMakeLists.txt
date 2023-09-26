cmake_minimum_required(VERSION 3.26)
project(cuda_neu CUDA)

set(CMAKE_CUDA_STANDARD 20)


add_executable(cuda_neu main.cu )

set_target_properties(cuda_neu PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
 

 
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
 


#SKIA
target_include_directories(cuda_neu PRIVATE "C:/skia")
target_include_directories(cuda_neu PRIVATE "C:/skia/include")


target_link_libraries(cuda_neu "C:/skia/out/vs/skia.lib")



#OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(cuda_neu OpenGL::GL)


set_property(TARGET cuda_neu PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
