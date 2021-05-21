// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021 Darby Johnston
// All rights reserved.

namespace tlr
{
    namespace timeline
    {
        inline const std::string& TimelinePlayer::getFileName() const
        {
            return _timeline->getFileName();
        }

        inline const otime::RationalTime& TimelinePlayer::getGlobalStartTime() const
        {
            return _timeline->getGlobalStartTime();
        }

        inline const otime::RationalTime& TimelinePlayer::getDuration() const
        {
            return _timeline->getDuration();;
        }

        inline const imaging::Info& TimelinePlayer::getImageInfo() const
        {
            return _timeline->getImageInfo();
        }

        inline std::vector<otime::TimeRange> TimelinePlayer::getClipRanges() const
        {
            return _timeline->getClipRanges();;
        }

        inline std::shared_ptr<Observer::IValueSubject<Playback> > TimelinePlayer::observePlayback() const
        {
            return _playback;
        }

        inline std::shared_ptr<Observer::IValueSubject<Loop> > TimelinePlayer::observeLoop() const
        {
            return _loop;
        }

        inline std::shared_ptr<Observer::IValueSubject<otime::RationalTime> > TimelinePlayer::observeCurrentTime() const
        {
            return _currentTime;
        }

        inline std::shared_ptr<Observer::IValueSubject<otime::TimeRange> > TimelinePlayer::observeInOutRange() const
        {
            return _inOutRange;
        }

        inline std::shared_ptr<Observer::IValueSubject<io::VideoFrame> > TimelinePlayer::observeFrame() const
        {
            return _frame;
        }

        inline int TimelinePlayer::getFrameCacheReadAhead() const
        {
            return _frameCacheReadAhead;
        }

        inline int TimelinePlayer::getFrameCacheReadBehind() const
        {
            return _frameCacheReadBehind;
        }

        inline std::shared_ptr<Observer::IListSubject<otime::TimeRange> > TimelinePlayer::observeCachedFrames() const
        {
            return _cachedFrames;
        }
    }
}