#include "../../include/server/string_utils.h"

bool StringUtils::Contains(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}