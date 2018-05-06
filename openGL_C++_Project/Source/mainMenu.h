#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED
#include "myLibrary.h"
#include "circles.h"
#include "bezier.h"
#include "tween.h"
#include "clip.h"
#include "mirror.h"
#include "reflect.h"

void mainMenu();
inline void realMainMouse(int, bool, int, int);
void mainMouse(int, int, int, int);
void mainKeyboard(unsigned char, int, int);
void mainSpecial(int, int, int);
void mainPassive(int, int);
void room_goto(int);



#endif // MAINMENU_H_INCLUDED
