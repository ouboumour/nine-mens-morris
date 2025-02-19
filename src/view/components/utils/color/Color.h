#ifndef COLOR_H
#define COLOR_H

typedef struct {
    int r;
    int g;
    int b;
    int a;
} RgbaColor;

typedef enum {
    BLACK,
    BLUE,
    GREEN,
    WHITE
} Color;

RgbaColor toRgba(Color color);
Color pickColorFromComponentId(const char* componentId);

#endif //COLOR_H
