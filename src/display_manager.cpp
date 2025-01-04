#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <vector>
#include <string>

struct ScreenResolution {
    int width;
    int height;
    std::string monitor_name;
};

// Platform-specific resolution handling
std::vector<ScreenResolution> getResolutionsForPlatform();
void setResolutionForPlatform(int width, int height);

#endif // DISPLAY_MANAGER_H
