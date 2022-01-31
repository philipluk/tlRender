// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

namespace tlr
{
    namespace render
    {
        inline bool Color::operator == (const Color& other) const
        {
            return
                add == other.add &&
                brightness == other.brightness &&
                contrast == other.contrast &&
                saturation == other.saturation &&
                tint == other.tint &&
                invert == other.invert;
        }

        inline bool Color::operator != (const Color& other) const
        {
            return !(*this == other);
        }

        inline bool Levels::operator == (const Levels& other) const
        {
            return
                inLow == other.inLow &&
                inHigh == other.inHigh &&
                gamma == other.gamma &&
                outLow == other.outLow &&
                outHigh == other.outHigh;
        }

        inline bool Levels::operator != (const Levels& other) const
        {
            return !(*this == other);
        }

        inline bool Exposure::operator == (const Exposure& other) const
        {
            return
                exposure == other.exposure &&
                defog == other.defog &&
                kneeLow == other.kneeLow &&
                kneeHigh == other.kneeHigh;
        }

        inline bool Exposure::operator != (const Exposure& other) const
        {
            return !(*this == other);
        }

        inline bool ImageOptions::operator == (const ImageOptions& other) const
        {
            return
                yuvRange == other.yuvRange &&
                channels == other.channels &&
                alphaBlend == other.alphaBlend &&
                mirror == other.mirror &&
                colorEnabled == other.colorEnabled &&
                color == other.color &&
                levelsEnabled == other.levelsEnabled &&
                levels == other.levels &&
                exposureEnabled == other.exposureEnabled &&
                exposure == other.exposure &&
                softClipEnabled == other.softClipEnabled &&
                softClip == other.softClip;
        }

        inline bool ImageOptions::operator != (const ImageOptions& other) const
        {
            return !(*this == other);
        }

        inline bool CompareOptions::operator == (const CompareOptions& other) const
        {
            return
                mode == other.mode &&
                horizontal == other.horizontal &&
                vertical == other.vertical &&
                freePos == other.freePos &&
                freeRot == other.freeRot;
        }

        inline bool CompareOptions::operator != (const CompareOptions& other) const
        {
            return !(*this == other);
        }
    }
}