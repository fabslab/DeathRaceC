#pragma once

#include <string>

// Returns the full path to an asset by prepending the executable's directory.
// Use this instead of hardcoded "Content/..." paths so the game works
// regardless of the working directory at launch.
std::string GetAssetPath(const char* relativePath);
