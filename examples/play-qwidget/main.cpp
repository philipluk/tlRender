// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#include "App.h"

#include <tlrQWidget/Util.h>

#include <iostream>

int main(int argc, char* argv[])
{
    int r = 0;
    try
    {
        tlr::qwidget::init();
        tlr::App app(argc, argv);
        if (0 == app.getExit())
        {
            r = app.exec();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return r;
}