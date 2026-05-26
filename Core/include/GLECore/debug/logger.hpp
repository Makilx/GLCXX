#pragma once

#include <GLECore/enum/log.hpp>
#include <GLECore/math/color.hpp>
#include <GLECore/pch.hpp>

namespace gle {
    void Write(LogType type, const std::string &message);
    void WriteCustom(const std::string &message, const Color &color, const std::string &tag, bool showTime = true);
    void Clear();
    std::string Read(std::string message = "");
} // namespace gle