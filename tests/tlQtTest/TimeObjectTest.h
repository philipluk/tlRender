// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tlTestLib/ITest.h>

namespace tl
{
    namespace QtTest
    {
        class TimeObjectTest : public Test::ITest
        {
        protected:
            TimeObjectTest(const std::shared_ptr<core::Context>&);

        public:
            static std::shared_ptr<TimeObjectTest> create(const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}