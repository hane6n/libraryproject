#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <string>
#include <algorithm>

inline std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token = "";
    for (char ch : s) {
        if (ch != delimiter) token += ch;
        else {
            if (!token.empty()) tokens.push_back(token);
            token = "";
        }
    }
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

template<typename T, typename Predicate>
void sortData(std::vector<T>& data, Predicate pred) {
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = i + 1; j < data.size(); j++) {
            if (pred(data[j], data[i])) {
                T temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}
#endif