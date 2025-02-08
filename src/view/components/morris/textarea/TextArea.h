#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "../commons/Commons.h"

typedef struct {
  char* id;
  char* text;
  Coordinates coordinates;
} TextArea;

void renderTextArea(TextArea textArea);

#endif //TEXTAREA_H
