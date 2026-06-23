#ifndef SMART_HOSPITAL_UTILITY_H
#define SMART_HOSPITAL_UTILITY_H

#include <algorithm>
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace smart_hospital {
namespace util {

std::string trim(const std::string& value);
std::vector<std::string> split(const std::string& value, char delimiter);
std::string join(const std::vector<std::string>& values, char delimiter);
int toInt(const std::string& value, const std::string& fieldName);
std::string currentDateTime();
void ensureDataFile(const std::string& filePath);

template <typename T>
T clampValue(T value, T low, T high) {
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

template <typename T>
T average(const std::vector<T>& values) {
    if (values.empty()) {
        return T{};
    }

    T total{};
    for (const auto& value : values) {
        total += value;
    }
    return static_cast<T>(total / static_cast<T>(values.size()));
}

template <typename T>
class Repository {
private:
    std::vector<std::shared_ptr<T>> records;

public:
    Repository() = default;

    void add(const std::shared_ptr<T>& record) {
        if (!record) {
            throw std::invalid_argument("Cannot add an empty record.");
        }
        records.push_back(record);
    }

    bool removeById(const std::string& id) {
        const auto oldSize = records.size();
        records.erase(
            std::remove_if(records.begin(), records.end(),
                           [&](const std::shared_ptr<T>& item) {
                               return item && item->getId() == id;
                           }),
            records.end());
        return records.size() != oldSize;
    }

    std::shared_ptr<T> findById(const std::string& id) const {
        auto found = std::find_if(records.begin(), records.end(),
                                  [&](const std::shared_ptr<T>& item) {
                                      return item && item->getId() == id;
                                  });
        return found == records.end() ? nullptr : *found;
    }

    std::vector<std::shared_ptr<T>>& all() {
        return records;
    }

    const std::vector<std::shared_ptr<T>>& all() const {
        return records;
    }

    std::size_t size() const {
        return records.size();
    }

    void clear() {
        records.clear();
    }

    template <typename Compare>
    void sortBy(Compare compare) {
        std::sort(records.begin(), records.end(), compare);
    }
};

} // namespace util
} // namespace smart_hospital

#endif
