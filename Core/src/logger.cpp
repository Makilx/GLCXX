#include <GLECore/debug/logger.hpp>
#include <cctype>
#include <chrono>
#include <ctime>
#include <future>

std::string GetTimestamp() {
    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t time = system_clock::to_time_t(now);

    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    char buffer[9]; // HH:MM:SS
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &localTime);

    return buffer;
}

std::string GetColorANSI(std::string hex) {
    // Fallback: default terminal color
    constexpr const char *fallback = "\x1b[0m";

    if (hex.size() != 7 || hex[0] != '#')
        return fallback;

    // Validate hex characters first
    for (size_t i = 1; i < 7; ++i) {
        if (!std::isxdigit(static_cast<unsigned char>(hex[i])))
            return fallback;
    }

    // Manual hex parsing (no stoi, no exceptions)
    auto hexToInt = [](char c) -> int {
        if (c >= '0' && c <= '9')
            return c - '0';
        if (c >= 'a' && c <= 'f')
            return 10 + (c - 'a');
        if (c >= 'A' && c <= 'F')
            return 10 + (c - 'A');
        return 0;
    };

    int r = hexToInt(hex[1]) * 16 + hexToInt(hex[2]);
    int g = hexToInt(hex[3]) * 16 + hexToInt(hex[4]);
    int b = hexToInt(hex[5]) * 16 + hexToInt(hex[6]);

    return "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

void gle::WriteCustom(const std::string &message, const Color &color, const std::string &tag, bool showTime) {
    std::string tagResult = tag.size() > 0 ? "[" + tag + "] " : "";
    std::cout << GetColorANSI(color.ToHEX()) << "[" << GetTimestamp() << "]" << tagResult << message << "\x1b[0m"
              << std::endl;
}

void gle::Write(LogType type, const std::string &message) {
    Color writeColor;
    std::string writeTag;

    switch (type) {
    case LogType::Log:
        writeColor = Color::FromHEX("#b8cfde");
        writeTag = "LOG    ";
        break;
    case LogType::Output:
        writeColor = Color::FromHEX("#79beec");
        writeTag = "OUTPUT ";
        break;
    case LogType::Warning:
        writeColor = Color::FromHEX("#ecb879");
        writeTag = "WARNING";
        break;
    case LogType::Error:
        writeColor = Color::FromHEX("#ec7979");
        writeTag = "ERROR  ";
        break;
    case LogType::Debug:
        writeColor = Color::FromHEX("#cd79ec");
        writeTag = "DEBUG  ";
        break;
    case LogType::Success:
        writeColor = Color::FromHEX("#98ec79");
        writeTag = "SUCCESS";
        break;
    case LogType::Lethal:
        writeColor = Color::FromHEX("#662b2c");
        writeTag = "FATAL  ";
        break;
    }

    WriteCustom(message, writeColor, writeTag, true);
}

void gle::Clear() {
    system("cls");
}

std::string gle::Read(std::string message) {
    static std::future<std::string> inputFuture;
    static bool isWaiting = false;
    static bool promptPrinted = false;

    // Phase 1: Start the thread and print the prompt
    if (!isWaiting) {
        if (!promptPrinted) {
            std::cout << message << std::flush; // Print prompt without newline
            promptPrinted = true;
        }

        inputFuture = std::async(std::launch::async, []() {
            std::string line;
            std::getline(std::cin, line);
            return line;
        });
        isWaiting = true;
    }

    // Phase 2: Poll for completion
    if (inputFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        std::string result = inputFuture.get();

        // Reset all states for the next time Input() is called
        isWaiting = false;
        promptPrinted = false;

        return result;
    }

    // Still waiting for user to press Enter
    return "";
}