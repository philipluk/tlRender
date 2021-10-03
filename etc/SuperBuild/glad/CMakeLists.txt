cmake_minimum_required(VERSION 3.0)

project(glad LANGUAGES C)

include_directories(${CMAKE_SOURCE_DIR}/include)

if ("GL" STREQUAL TLR_GL_VERSION)
    set(HEADERS include/glad/gl.h)
    set(SOURCE src/gl.c)
elseif ("GLES2" STREQUAL TLR_GL_VERSION)
    set(HEADERS include/glad/gles2.h)
    set(SOURCE src/gles2.c src/egl.c)
endif()

add_library(glad ${HEADERS} ${SOURCE})

install(
    TARGETS glad
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES ${HEADERS} DESTINATION include/glad)
if ("GLES2" STREQUAL TLR_GL_VERSION)
    install(FILES include/KHR/khrplatform.h DESTINATION include/KHR)
    install(FILES include/EGL/eglplatform.h DESTINATION include/EGL)
endif()
