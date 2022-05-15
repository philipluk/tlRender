include(ExternalProject)

set(OTIO_GIT_REPOSITORY "https://github.com/PixarAnimationStudios/OpenTimelineIO.git")
set(OTIO_GIT_TAG v0.14.1)

set(OTIO_SHARED_LIBS ON)
if(NOT BUILD_SHARED_LIBS)
    set(OTIO_SHARED_LIBS OFF)
endif()

set(OTIO_ARGS
    ${TLRENDER_EXTERNAL_ARGS}
    -DOTIO_SHARED_LIBS=${OTIO_SHARED_LIBS}
    -DOTIO_PYTHON_INSTALL=${TLRENDER_ENABLE_PYTHON}
    -DOTIO_PYTHON_INSTALL_DIR_INITIALIZED_TO_DEFAULT=TRUE)

ExternalProject_Add(
    OTIO
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/OTIO
    DEPENDS ${OTIO_DEPENDS}
    GIT_REPOSITORY ${OTIO_GIT_REPOSITORY}
    GIT_TAG ${OTIO_GIT_TAG}
    LIST_SEPARATOR |
    CMAKE_ARGS ${OTIO_ARGS})
