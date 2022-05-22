// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tlCore/Image.h>
#include <tlCore/Time.h>

namespace tl
{
    namespace device
    {
        //! Display mode.
        struct DisplayMode
        {
            std::string name;
            imaging::Size size;
            otime::RationalTime frameRate;

            bool operator == (const DisplayMode&) const;
        };

        //! Pixel types.
        enum class PixelType
        {
            None,
            _8BitBGRA,
            _10BitRGB,
            _10BitRGBX,
            _10BitRGBXLE,

            Count,
            First = None
        };
        TLRENDER_ENUM(PixelType);
        TLRENDER_ENUM_SERIALIZE(PixelType);

        //! Get the number of bytes used to store the pixel data.
        size_t getDataByteCount(const imaging::Size&, PixelType);

        //! Pixel data.
        class PixelData : public std::enable_shared_from_this<PixelData>
        {
            TLRENDER_NON_COPYABLE(PixelData);

        protected:
            void _init(const imaging::Size&, PixelType);
            PixelData();

        public:
            ~PixelData();

            //! Create new pixel data.
            static std::shared_ptr<PixelData> create(const imaging::Size&, PixelType);

            //! Get the pixel data size.
            const imaging::Size& getSize() const;

            //! Get the pixel type.
            PixelType getPixelType() const;

            //! Is the pixel data valid?
            bool isValid() const;

            //! Get the number of bytes used to store the pixel data.
            size_t getDataByteCount() const;

            //! Get the pixel data.
            const uint8_t* getData() const;

            //! Get the pixel data.
            uint8_t* getData();

            //! Zero the pixel data.
            void zero();

        private:
            imaging::Size _size;
            PixelType _pixelType = PixelType::None;
            size_t _dataByteCount = 0;
            uint8_t* _data = nullptr;
        };

        //! Device information.
        struct DeviceInfo
        {
            std::string name;
            std::vector<DisplayMode> displayModes;
            std::vector<PixelType> pixelTypes;

            bool operator == (const DeviceInfo&) const;
        };
    }
}