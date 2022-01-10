// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#include <tlrCoreTest/TimelineUtilTest.h>

#include <tlrCore/Assert.h>
#include <tlrCore/TimelineUtil.h>

#include <opentimelineio/clip.h>

using namespace tlr::timeline;

namespace tlr
{
    namespace CoreTest
    {
        TimelineUtilTest::TimelineUtilTest(const std::shared_ptr<core::Context>& context) :
            ITest("CoreTest::TimelineUtilTest", context)
        {}

        std::shared_ptr<TimelineUtilTest> TimelineUtilTest::create(const std::shared_ptr<core::Context>& context)
        {
            return std::shared_ptr<TimelineUtilTest>(new TimelineUtilTest(context));
        }

        void TimelineUtilTest::run()
        {
            _enums();
            _ranges();
            _util();
        }

        void TimelineUtilTest::_enums()
        {
            _enum<FileSequenceAudio>("FileSequenceAudio", getFileSequenceAudioEnums);
        }
        
        void TimelineUtilTest::_ranges()
        {
            {
                std::vector<otime::RationalTime> f;
                auto r = toRanges(f);
                TLR_ASSERT(r.empty());
            }
            {
                std::vector<otime::RationalTime> f =
                {
                    otime::RationalTime(0, 24)
                };
                auto r = toRanges(f);
                TLR_ASSERT(1 == r.size());
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(0, 24), otime::RationalTime(1, 24)) == r[0]);
            }
            {
                std::vector<otime::RationalTime> f =
                {
                    otime::RationalTime(0, 24),
                    otime::RationalTime(1, 24)
                };
                auto r = toRanges(f);
                TLR_ASSERT(1 == r.size());
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(0, 24), otime::RationalTime(2, 24)) == r[0]);
            }
            {
                std::vector<otime::RationalTime> f =
                {
                    otime::RationalTime(0, 24),
                    otime::RationalTime(1, 24),
                    otime::RationalTime(2, 24)
                };
                auto r = toRanges(f);
                TLR_ASSERT(1 == r.size());
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(0, 24), otime::RationalTime(3, 24)) == r[0]);
            }
            {
                std::vector<otime::RationalTime> f =
                {
                    otime::RationalTime(0, 24),
                    otime::RationalTime(2, 24)
                };
                auto r = toRanges(f);
                TLR_ASSERT(2 == r.size());
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(0, 24), otime::RationalTime(1, 24)) == r[0]);
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(2, 24), otime::RationalTime(1, 24)) == r[1]);
            }
            {
                std::vector<otime::RationalTime> f =
                {
                    otime::RationalTime(0, 24),
                    otime::RationalTime(1, 24),
                    otime::RationalTime(3, 24)
                };
                auto r = toRanges(f);
                TLR_ASSERT(2 == r.size());
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(0, 24), otime::RationalTime(2, 24)) == r[0]);
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(3, 24), otime::RationalTime(1, 24)) == r[1]);
            }
            {
                std::vector<otime::RationalTime> f =
                {
                    otime::RationalTime(0, 24),
                    otime::RationalTime(1, 24),
                    otime::RationalTime(3, 24),
                    otime::RationalTime(4, 24)
                };
                auto r = toRanges(f);
                TLR_ASSERT(2 == r.size());
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(0, 24), otime::RationalTime(2, 24)) == r[0]);
                TLR_ASSERT(otime::TimeRange(otime::RationalTime(3, 24), otime::RationalTime(2, 24)) == r[1]);
            }
        }
        
        void TimelineUtilTest::_util()
        {
            {
                auto otioClip = new otio::Clip;
                otio::ErrorStatus errorStatus;
                auto otioTrack = new otio::Track();
                otioTrack->append_child(otioClip, &errorStatus);
                if (errorStatus != otio::ErrorStatus::OK)
                {
                    throw std::runtime_error("Cannot append child");
                }
                auto otioStack = new otio::Stack;
                otioStack->append_child(otioTrack, &errorStatus);
                if (errorStatus != otio::ErrorStatus::OK)
                {
                    throw std::runtime_error("Cannot append child");
                }
                otio::SerializableObject::Retainer<otio::Timeline> otioTimeline(new otio::Timeline);
                otioTimeline->set_tracks(otioStack);
                TLR_ASSERT(otioStack == getRoot(otioClip));
                TLR_ASSERT(otioStack == getParent<otio::Stack>(otioClip));
                TLR_ASSERT(otioTrack == getParent<otio::Track>(otioClip));
            }
            {
                VideoData a;
                a.time = otime::RationalTime(1.0, 24.0);
                VideoData b;
                b.time = otime::RationalTime(1.0, 24.0);
                TLR_ASSERT(isTimeEqual(a, b));
            }
        }

    }
}
