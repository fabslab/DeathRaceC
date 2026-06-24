#include "AssetPath.h"
#include "raylib.h"
#include <string>

std::string GetAssetPath(const char* relativePath)
{
    const char* appDir = GetApplicationDirectory();
    if (appDir == nullptr || std::strlen(appDir) == 0) {
        return relativePath;
    }
    std::string path(appDir);
    // Ensure trailing separator
    if (!path.empty() && path.back() != '/' && path.back() != '\\') {
        path += '/';
    }
    path += relativePath;
    return path;
}
