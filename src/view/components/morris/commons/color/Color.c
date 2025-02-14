#include "Color.h"

#include <string.h>

RgbaColor toRgba(const Color color) {
    switch (color) {
        case BLUE:
            return (RgbaColor){39, 153, 255, 255};
        case WHITE:
            return (RgbaColor){255, 255, 255, 255};
        case GREEN:
            return (RgbaColor){42, 185, 75, 255};
        default:
            return (RgbaColor){0, 0, 0, 255};
    }
}

Color pickColorFromComponentId(const char* componentId) {
    if (strstr(componentId, ":blue") != NULL) return BLUE;
    if (strstr(componentId, ":green") != NULL) return GREEN;
    if (strstr(componentId, ":white") != NULL) return WHITE;
    return BLACK;
}
