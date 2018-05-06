#ifndef CLIP_H_INCLUDED
#define CLIP_H_INCLUDED
#include "mainMenu.h"

void clipDisplay();
inline void realclipMouse(int, bool, int, int);
void clipMouse(int, int, int, int);
void clipMotion(int, int);
void clipKeyboard(unsigned char, int, int);
void clipSpecial(int, int, int);
void clipPassive(int, int);


#endif // CLIP_H_INCLUDED
