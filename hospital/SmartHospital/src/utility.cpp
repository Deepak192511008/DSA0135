#include "utility.h"

#include <chrono>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace smart_hospital {
namespace util {

std::string trim(const std::string& value) {
    auto begin = value.begin();
    while (begin != value.end() && std::isspace(static_cast<unsigned char>(*begin))) {
        ++begin;
    }

    auto end = value.end();
    do {
        if (begin == end) {
            return "";
        }
        --end;
    } while (std::isspace(static_cast<unsigned char>(*end)));

    return std::string(begin, end + 1);
}

std::vector<std::string> split(const std::string& value, char delimiter) {
    std::vector<std::string> result;
    std::stringstream stream(value);
    std::string item;
    while (std::getline(stream, item, delimiter)) {
        result.push_back(trim(item));
    }
    return result;
}

std::string join(const std::vector<std::string>& values, char delimiter) {
    std::ostringstream out;
    for (std::size_t index = 0; index < values.size(); ++index) {
        if (index > 0) {
            out << delimiter;
        }
        out << values[index];
    }
    return out.str();
}

int toInt(const std::string& value, const std::string& fieldName) {
    try {
        std::size_t processed = 0;
        const int number = std::stoi(trim(value), &processed);
        if (processed != trim(value).size()) {
            throw std::invalid_argument("extra characters");
        }
        return number;
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid integer for " + fieldName + ": " + value);
    }
}

std::string currentDateTime() {
    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tmValue{};
    const std::tm* localTime = std::localtime(&time);
    if (localTime != nullptr) {
        tmValue = *localTime;
    }

    std::ostringstream out;
    out << std::put_time(&tmValue, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

void ensureDataFile(const std::string& filePath) {
    std::fstream file(filePath, std::ios::in);
    if (!file.good()) {
        file.close();
        std::ofstream create(filePath);
    }
}

} // namespace util
} // namespace smart_hospital
