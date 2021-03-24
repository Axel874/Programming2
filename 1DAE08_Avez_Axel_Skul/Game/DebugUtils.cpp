#include "pch.h"
#include "DebugUtils.h"
namespace utils {
	void LogWarning(const std::string& message, const char* file, const int& line) {
		std::cout << file << "::" << line << " : ";
		std::cout << message << std::endl;
	}
}

