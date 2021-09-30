include(ExternalProject)

set(PNG_GIT_REPOSITORY "https://github.com/glennrp/libpng.git")
set(PNG_GIT_TAG "a40189cf881e9f0db80511c382292a5604c3c3d1") # tag: v1.6.37

set(PNG_SHARED_LIBS ON)
set(PNG_STATIC_LIBS OFF)
if(NOT BUILD_SHARED_LIBS)
    set(PNG_SHARED_LIBS OFF)
    set(PNG_STATIC_LIBS ON)
endif()

set(PNG_ARGS
    ${TLR_EXTERNAL_ARGS}
    -DCMAKE_INSTALL_LIBDIR=lib
    -DPNG_SHARED=${PNG_SHARED_LIBS}
    -DPNG_STATIC=${PNG_STATIC_LIBS}
    -DPNG_TESTS=OFF
    -DPNG_ARM_NEON=off
    -DSKIP_INSTALL_EXECUTABLES=ON
    -DSKIP_INSTALL_PROGRAMS=ON
    -DSKIP_INSTALL_FILES=ON)

ExternalProject_Add(
    PNG
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/PNG
    DEPENDS ZLIB
    GIT_REPOSITORY ${PNG_GIT_REPOSITORY}
    GIT_TAG ${PNG_GIT_TAG}
    PATCH_COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/PNG-patch/CMakeLists.txt
        ${CMAKE_CURRENT_BINARY_DIR}/PNG/src/PNG/CMakeLists.txt
    LIST_SEPARATOR |
    CMAKE_ARGS ${PNG_ARGS})
