#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "../../utils/commons/Commons.h"
#include "../../surface/SurfaceComponent.h"

typedef struct {
  char* id;
  char* text;
  Coordinates coordinates;
  Alignement alignement;
} TextArea;

void renderTextArea(TextArea textArea);

#endif //TEXTAREA_H
