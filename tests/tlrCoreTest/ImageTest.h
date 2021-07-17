// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021 Darby Johnston
// All rights reserved.

#pragma once

#include <tlrTestLib/ITest.h>

namespace tlr
{
    namespace CoreTest
    {
        class ImageTest : public Test::ITest
        {
        protected:
            ImageTest(const std::shared_ptr<core::Context>&);

        public:
            static std::shared_ptr<ImageTest> create(const std::shared_ptr<core::Context>&);

            void run() override;
            
        private:
            void _size();
            void _enums();
            void _info();
            void _util();
            void _image();
        };
    }
}
