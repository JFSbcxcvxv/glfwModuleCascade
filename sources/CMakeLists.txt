project(sources)


set(THIRD_PARTY_PATH ${CMAKE_SOURCE_DIR}/external/occt)
message(${CMAKE_SOURCE_DIR})

include_directories(${THIRD_PARTY_PATH}/inc)
#windows path
if (WIN32)
    link_directories(${THIRD_PARTY_PATH}/win64/gcc/libd)
endif (WIN32)
if (UNIX)
#linux path
    link_directories(${THIRD_PARTY_PATH}/lin64/gcc/libd)
endif (UNIX)



set(OpenCASCADE_Component
  TKernel TKService TKV3d TKOpenGl
  TKBRep TKGeomBase TKGeomAlgo TKG3d TKG2d TKTopAlgo
  TKPrim TKMath TKBin TKBool TKBO TKFillet
  TKOffset TKTObj TKFeat TKMesh TKOffset TKXSBase
  TKDESTEP TKDEIGES TKDESTL TKDEVRML TKLCAF
)

list(APPEND myApp_HEADER
    ${CMAKE_CURRENT_LIST_DIR}/GlfwOcctView.h
    ${CMAKE_CURRENT_LIST_DIR}/GlfwOcctWindow.h
)

list(APPEND myApp_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/GlfwOcctView.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GlfwOcctWindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${myApp_HEADER} ${myApp_SOURCES}
    interfaceimgui.h
    interfaceimgui.cpp
    modelingcascade.h
    modelingcascade.cpp
    L2DFileDialog.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        external
        ${OPENGL_INCLUDE_DIR}
)



target_link_libraries(${PROJECT_NAME}
        ${OPENGL_gl_LIBRARY}
        glfw
        imgui
        spdlog::spdlog
        ${OpenCASCADE_Component}
)
