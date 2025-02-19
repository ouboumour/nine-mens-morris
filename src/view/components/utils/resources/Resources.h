#ifndef RESOURCES_H
#define RESOURCES_H

#ifdef __EMSCRIPTEN__
    #define IMAGES_PATH "/assets/images/"
    #define FONTS_PATH "/assets/fonts/"
#else
    #define IMAGES_PATH "../src/view/assets/images/"
    #define FONTS_PATH "../src/view/assets/fonts/"
#endif

#endif //RESOURCES_H
