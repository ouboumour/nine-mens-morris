#include "AnimationComponent.h"
//
// typedef struct Animation {
//     char* id;
//     IMG_Animation* sdlAnimation;
//     struct Animation* next;
// } Animation;
//
// IMG_Animation* findAnimationById(const char* id);
// IMG_Animation* createNewAnimation(const char* id);
//
// Animation* animationHead = NULL;
//
// IMG_Animation* createAnimation(const char* id) {
//     IMG_Animation* animation = findAnimationById(id);
//     return animation != NULL ? animation : createNewAnimation(id);
// }
//
// IMG_Animation* findAnimationById(const char* id) {
//     const Animation* currentAnimation = animationHead;
//     while (currentAnimation != NULL) {
//         if (strcmp(currentAnimation->id, id) == 0) {
//             return currentAnimation->sdlAnimation;
//         }
//         currentAnimation = currentAnimation->next;
//     }
//     return NULL;
// }
//
// IMG_Animation* createNewAnimation(const char* id) {
//     char gifPath[100];
//     sprintf(gifPath, "../src/view/assets/images/%s.gif", id);
//     const IMG_Animation* newSdlAnimation = IMG_LoadAnimation(id);
//
//     if (newSdlAnimation == NULL) {
//         // handleSDLTextureInitFailure(textureName);
//         exit(-1);
//     }
//
//     Animation* newAnimation = malloc(sizeof(Animation));
//     if (newAnimation == NULL) {
//
//     }
//
// }