#include "string_extensions.h"

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

namespace protoc_js_gen_plugin {
namespace {

std::vector<std::string> SplitString(const std::string& str, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(str);
    std::string part;
    while (std::getline(ss, part, delimiter)) {
        parts.push_back(part);
    }
    return parts;
}

std::string ToUpperUnderscore(const std::string& camel) {
    std::string result;
    for (char c : camel) {
        if (std::isupper(static_cast<unsigned char>(c)) && !result.empty()) {
            result += '_';
        }
        result += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return result;
}

bool StartsWithIgnoreCase(const std::string& str, const std::string& prefix) {
    if (str.size() < prefix.size())
        return false;
    for (size_t i = 0; i < prefix.size(); ++i) {
        if (std::tolower(static_cast<unsigned char>(str[i])) !=
            std::tolower(static_cast<unsigned char>(prefix[i]))) {
            return false;
        }
    }
    return true;
}
}  // namespace

std::string SnakeToCamelCase(const std::string& snake_case) {
    if (snake_case.empty()) return snake_case;

    auto parts = SplitString(snake_case, '_');
    std::string result;

    for (size_t i = 0; i < parts.size(); ++i) {
        const auto& part = parts[i];
        if (part.empty()) continue;

        if (i == 0) {
            // First word stays lowercase
            result += part;
        } else {
            // Subsequent words start with uppercase
            result += static_cast<char>(std::toupper(static_cast<unsigned char>(part[0])));
            if (part.size() > 1) {
                result += part.substr(1);
            }
        }
    }

    return result;
}

std::string SnakeToPascalCase(const std::string& snake_case) {
    if (snake_case.empty()) return snake_case;

    auto parts = SplitString(snake_case, '_');
    std::string result;

    for (const auto& part : parts) {
        if (part.empty()) continue;

        result += static_cast<char>(std::toupper(static_cast<unsigned char>(part[0])));
        if (part.size() > 1) {
            result += part.substr(1);
        }
    }

    return result;
}

std::string StripEnumValuePrefix(const std::string& enum_name, const std::string& value_name) {
    if (enum_name.empty() || value_name.empty()) {
        return value_name;
    }

    {
        std::string prefix = enum_name + "_";
        if (StartsWithIgnoreCase(value_name, prefix)) {
            return value_name.substr(prefix.size());
        }
    }

    {
        std::string upper_prefix = ToUpperUnderscore(enum_name) + "_";
        if (StartsWithIgnoreCase(value_name, upper_prefix)) {
            return value_name.substr(upper_prefix.size());
        }
    }

    return value_name;
}
}  // namespace protoc_js_gen_plugin