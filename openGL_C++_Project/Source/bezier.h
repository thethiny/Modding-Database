#ifndef BEZIER_H_INCLUDED
#define BEZIER_H_INCLUDED
#include "mainMenu.h"


void bezierDisplay();
inline void realbezierMouse(int, bool, int, int);
void bezierMouse(int, int, int, int);
void bezierMotion(int, int);
void bezierKeyboard(unsigned char, int, int);
void bezierSpecial(int, int, int);
void bezierPassive(int, int);




#endif // BEZIER_H_INCLUDED
