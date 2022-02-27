// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tlApp/IApp.h>

#include <QApplication>

namespace tl
{
    namespace examples
    {
        //! Example showing the filmstrip widget.
        namespace filmstrip_qtwidget
        {
            //! Application.
            class App : public QApplication, public app::IApp
            {
                Q_OBJECT

            public:
                App(int& argc, char** argv);

            private:
                std::string _input;
            };
        }
    }
}