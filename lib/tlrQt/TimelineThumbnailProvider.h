// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021 Darby Johnston
// All rights reserved.

#pragma once

#include <tlrGL/Render.h>

#include <tlrCore/Timeline.h>

#include <QObject>
#include <QOffscreenSurface>
#include <QImage>

#include <atomic>
#include <mutex>
#include <thread>

namespace tlr
{
    namespace qt
    {
        //! Timeout for thumbnail requests.
        const std::chrono::microseconds thumbnailRequestTimeout(1000);

        //! The thumbnail timer interval.
        const int thumbnailTimerInterval = 10;

        //! Timeline thumbnail provider.
        class TimelineThumbnailProvider : public QObject
        {
            Q_OBJECT

        public:
            TimelineThumbnailProvider(
                const std::shared_ptr<tlr::timeline::Timeline>&,
                QObject* parent = nullptr);
            ~TimelineThumbnailProvider() override;

            //! Set the color configuration.
            void setColorConfig(const gl::ColorConfig&);

        public Q_SLOTS:
            //! Request a thumbnail.
            void request(const otime::RationalTime&, const QSize&);

            //! Request thumbnails.
            void request(const QList<otime::RationalTime>&, const QSize&);

            //! Cancel all thumbnail requests.
            void cancelRequests();

        Q_SIGNALS:
            //! This signal is emitted when thumbnails are ready.
            void thumbails(const QList<QPair<otime::RationalTime, QImage> >&);

        protected:
            void timerEvent(QTimerEvent*) override;

        private:
            std::shared_ptr<timeline::Timeline> _timeline;
            gl::ColorConfig _colorConfig;
            struct Request
            {
                otime::RationalTime time = invalidTime;
                QSize size;
            };
            std::list<Request> _requests;
            QList<QPair<otime::RationalTime, QImage> > _results;
            bool _cancelRequests = false;
            std::condition_variable _cv;
            std::mutex _mutex;
            std::thread _thread;
            std::atomic<bool> _running;
            QOffscreenSurface* _surface = nullptr;
        };
    }
}