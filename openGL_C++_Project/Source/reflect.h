#ifndef REFLECT_H_INCLUDED
#define REFLECT_H_INCLUDED
#include "mainMenu.h"

void reflectDisplay();
inline void realreflectMouse(int, bool, int, int);
void reflectMouse(int, int, int, int);
void reflectMotion(int, int);
void reflectKeyboard(unsigned char, int, int);
void reflectSpecial(int, int, int);
void reflectPassive(int, int);
void reflectDrag(int, int);

#endif // REFLECT_H_INCLUDED
