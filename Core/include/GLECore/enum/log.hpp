#pragma once

namespace gle {
    enum class LogType : unsigned int {
        Log,
        Output,
        Warning,
        Error,
        Debug,
        Success,
        Lethal
    };
} // namespace gle