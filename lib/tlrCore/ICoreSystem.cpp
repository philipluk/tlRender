// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#include <tlrCore/ICoreSystem.h>

namespace tlr
{
    namespace core
    {
        void ICoreSystem::_init(
            const std::string& name,
            const std::shared_ptr<Context>& context)
        {
            _context = context;
            _name = name;
        }

        ICoreSystem::ICoreSystem()
        {}

        ICoreSystem::~ICoreSystem()
        {}
    }
}