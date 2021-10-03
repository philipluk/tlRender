// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021 Darby Johnston
// All rights reserved.

#pragma once

#include <tlrCore/Image.h>

#if defined(TLR_GL)
#include <glad/gl.h>
#elif defined(TLR_GLES2)
#include <glad/gles2.h>
#endif

namespace tlr
{
    //! OpenGL support.
    namespace gl
    {
        //! Get the glReadPixels format.
        GLenum getReadPixelsFormat(imaging::PixelType);

        //! Get the glReadPixels type.
        GLenum getReadPixelsType(imaging::PixelType);
    }
}
