#pragma once

#include <string>

namespace protoc_js_gen_plugin {

// Converts snake_case to camelCase
std::string SnakeToCamelCase(const std::string& snake_case);

// Converts snake_case to PascalCase
std::string SnakeToPascalCase(const std::string& snake_case);

// Strips enum name prefix from enum value name
// e.g., StripEnumValuePrefix("RESOURCEID", "RESOURCEID_UI_LOGIN_PANEL") returns "UI_LOGIN_PANEL"
std::string StripEnumValuePrefix(const std::string& enum_name, const std::string& value_name);

}  // namespace protoc_js_gen_plugin