#ifndef APP_H
#define APP_H

#include <stdbool.h>

typedef bool (*isRunning)();
typedef void (*ShutDown)();

typedef struct {
    isRunning isRunning;
    ShutDown shutDown;
} App;

extern App app;

#endif //APP_H