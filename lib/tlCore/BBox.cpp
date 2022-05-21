// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#include <tlCore/BBox.h>

#include <tlCore/Error.h>
#include <tlCore/String.h>

#include <sstream>

namespace tl
{
    namespace math
    {
        std::ostream& operator << (std::ostream& os, const BBox2i& value)
        {
            os << value.min.x << "," << value.min.y << "-" << value.max.x << "," << value.max.y;
            return os;
        }

        std::ostream& operator << (std::ostream& os, const BBox2f& value)
        {
            os << value.min.x << "," << value.min.y << "-" << value.max.x << "," << value.max.y;
            return os;
        }

        std::istream& operator >> (std::istream& is, BBox2i& value)
        {
            std::string s;
            is >> s;
            auto split = string::split(s, '-');
            if (split.size() != 2)
            {
                throw error::ParseError();
            }
            {
                std::stringstream ss(split[0]);
                ss >> value.min;
            }
            {
                std::stringstream ss(split[1]);
                ss >> value.max;
            }
            return is;
        }

        std::istream& operator >> (std::istream& is, BBox2f& value)
        {
            std::string s;
            is >> s;
            auto split = string::split(s, '-');
            if (split.size() != 2)
            {
                throw error::ParseError();
            }
            {
                std::stringstream ss(split[0]);
                ss >> value.min;
            }
            {
                std::stringstream ss(split[1]);
                ss >> value.max;
            }
            return is;
        }
    }
}
