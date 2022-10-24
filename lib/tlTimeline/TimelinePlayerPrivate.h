// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tlTimeline/TimelinePlayer.h>

#include <atomic>
#include <mutex>
#include <thread>

namespace tl
{
    namespace timeline
    {
        enum class CacheDirection
        {
            Forward,
            Reverse
        };

        struct TimelinePlayer::Private
        {
            otime::RationalTime loopPlayback(const otime::RationalTime&);

            void cacheUpdate(
                const otime::RationalTime& currentTime,
                const otime::TimeRange& inOutRange,
                uint16_t videoLayer,
                double audioOffset,
                CacheDirection,
                const otime::RationalTime& cacheReadAhead,
                const otime::RationalTime& cacheReadBehind);

            void resetAudioTime();
            static int rtAudioCallback(
                void* outputBuffer,
                void* inputBuffer,
                unsigned int nFrames,
                double streamTime,
                RtAudioStreamStatus status,
                void* userData);
            static void rtAudioErrorCallback(
                RtAudioError::Type type,
                const std::string& errorText);

            void log(const std::shared_ptr<system::Context>&);

            PlayerOptions playerOptions;
            std::shared_ptr<Timeline> timeline;
            io::Info ioInfo;

            std::shared_ptr<observer::Value<double> > speed;
            std::shared_ptr<observer::Value<Playback> > playback;
            std::shared_ptr<observer::Value<Loop> > loop;
            std::shared_ptr<observer::Value<otime::RationalTime> > currentTime;
            std::shared_ptr<observer::Value<otime::TimeRange> > inOutRange;
            std::shared_ptr<observer::Value<uint16_t> > videoLayer;
            std::shared_ptr<observer::Value<VideoData> > video;
            std::shared_ptr<observer::Value<float> > volume;
            std::shared_ptr<observer::Value<bool> > mute;
            std::shared_ptr<observer::Value<double> > audioOffset;
            std::shared_ptr<observer::Value<otime::RationalTime> > cacheReadAhead;
            std::shared_ptr<observer::Value<otime::RationalTime> > cacheReadBehind;
            std::shared_ptr<observer::Value<float> > cachePercentage;
            std::shared_ptr<observer::List<otime::TimeRange> > cachedVideoFrames;
            std::shared_ptr<observer::List<otime::TimeRange> > cachedAudioFrames;

            struct ExternalTime
            {
                std::shared_ptr<TimelinePlayer> player;
                std::shared_ptr<observer::ValueObserver<Playback> > playbackObserver;
                std::shared_ptr<observer::ValueObserver<otime::RationalTime> > currentTimeObserver;
            };
            ExternalTime externalTime;

            struct MutexData
            {
                Playback playback = Playback::Stop;
                otime::RationalTime playbackStartTime = time::invalidTime;
                std::chrono::steady_clock::time_point playbackStartTimer;
                otime::RationalTime currentTime = time::invalidTime;
                bool externalTime = false;
                otime::TimeRange inOutRange = time::invalidTimeRange;
                uint16_t videoLayer = 0;
                VideoData videoData;
                double audioOffset = 0.0;
                bool clearRequests = false;
                std::vector<otime::TimeRange> cachedVideoFrames;
                std::vector<otime::TimeRange> cachedAudioFrames;
                bool clearCache = false;
                CacheDirection cacheDirection = CacheDirection::Forward;
                otime::RationalTime cacheReadAhead = time::invalidTime;
                otime::RationalTime cacheReadBehind = time::invalidTime;
            };
            MutexData mutexData;
            std::mutex mutex;

            struct AudioMutexData
            {
                double speed = 0.0;
                float volume = 1.F;
                bool mute = false;
                std::chrono::steady_clock::time_point muteTimeout;
                std::map<int64_t, AudioData> audioDataCache;
                size_t rtAudioCurrentFrame = 0;
            };
            AudioMutexData audioMutexData;
            std::mutex audioMutex;

            struct ThreadData
            {
                std::map<otime::RationalTime, std::future<VideoData> > videoDataRequests;
                std::map<otime::RationalTime, VideoData> videoDataCache;
                std::unique_ptr<RtAudio> rtAudio;
                std::map<int64_t, std::future<AudioData> > audioDataRequests;
                std::atomic<bool> running;
            };
            ThreadData threadData;
            std::thread thread;

            std::chrono::steady_clock::time_point logTimer;
        };
    }
}