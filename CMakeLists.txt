cmake_minimum_required(VERSION 3.5)


project(glfwModuleCascade
    VERSION 0.0.2
    LANGUAGES C CXX
)

set(APP_TARGET glfwocct)

set(CMAKE_CXX_STANDARD 20)
set_target_properties(${TARGET} PROPERTIES

    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    CMAKE_CXX_EXTENSIONS OFF
)

# #find_package(Threads REQUIRED)
# #set(CMAKE_BUILD_PARALLEL_LEVEL 4)

# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)


add_subdirectory(external)
add_subdirectory(sources)





