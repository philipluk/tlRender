// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021 Darby Johnston
// All rights reserved.

#include <tlrCore/Cineon.h>

#include <tlrCore/StringFormat.h>

#include <sstream>

namespace tlr
{
    namespace cineon
    {
        void Read::_init(
            const std::string& fileName,
            const avio::Options& options)
        {
            ISequenceRead::_init(fileName, options);
        }

        Read::Read()
        {}

        Read::~Read()
        {}

        std::shared_ptr<Read> Read::create(
            const std::string& fileName,
            const avio::Options& options)
        {
            auto out = std::shared_ptr<Read>(new Read);
            out->_init(fileName, options);
            return out;
        }

        avio::Info Read::_getInfo(const std::string& fileName)
        {
            avio::Info out;
            auto io = file::FileIO::create();
            io->open(fileName, file::Mode::Read);
            Header::read(io, out);
            out.videoDuration = _defaultSpeed;
            return out;
        }

        avio::VideoFrame Read::_readVideoFrame(
            const std::string& fileName,
            const otime::RationalTime& time)
        {
            avio::VideoFrame out;
            out.time = time;
            avio::Info info;
            auto io = file::FileIO::create();
            io->open(fileName, file::Mode::Read);
            Header::read(io, info);
            out.image = imaging::Image::create(info.video[0]);
            io->read(out.image->getData(), imaging::getDataByteCount(info.video[0]));
            return out;
        }
    }
}