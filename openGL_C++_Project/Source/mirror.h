#ifndef MIRROR_H_INCLUDED
#define MIRROR_H_INCLUDED
#include "mainMenu.h"

void mainDraw();
void mirrorDisplay();
void mirrorDisplay2();
void mirrorReshape(int, int);
inline void realmirrorMouse(int, bool, int, int);
void mirrorMouse(int, int, int, int);
void mirrorMouse2(int, int, int, int);
void mirrorMotion(int, int);
void mirrorKeyboard(unsigned char, int, int);
void mirrorSpecial(int, int, int);
void mirrorPassive(int, int);

#endif // MIRROR_H_INCLUDED
