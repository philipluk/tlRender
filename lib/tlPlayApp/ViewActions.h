// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2023 Darby Johnston
// All rights reserved.

#pragma once

#include <tlQt/TimelinePlayer.h>

#include <QAction>
#include <QObject>
#include <QMenu>

#include <memory>

namespace tl
{
    namespace play
    {
        class App;

        //! View actions.
        class ViewActions : public QObject
        {
            Q_OBJECT

        public:
            ViewActions(App*, QObject* parent = nullptr);

            ~ViewActions() override;

            //! Get the actions.
            const QMap<QString, QAction*>& actions() const;

            //! Get the menu.
            QMenu* menu() const;

        private:
            void _actionsUpdate();

            TLRENDER_PRIVATE();
        };
    }
}
