// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tlTestLib/ITest.h>

namespace tl
{
    namespace tests
    {
        namespace io_test
        {
            class FFmpegTest : public Test::ITest
            {
            protected:
                FFmpegTest(const std::shared_ptr<core::system::Context>&);

            public:
                static std::shared_ptr<FFmpegTest> create(const std::shared_ptr<core::system::Context>&);

                void run() override;

            private:
                void _enums();
                void _util();
                void _io();
            };
        }
    }
}