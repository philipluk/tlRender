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
            class PNGTest : public Test::ITest
            {
            protected:
                PNGTest(const std::shared_ptr<core::system::Context>&);

            public:
                static std::shared_ptr<PNGTest> create(const std::shared_ptr<core::system::Context>&);

                void run() override;
            };
        }
    }
}