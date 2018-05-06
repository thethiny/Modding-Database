#ifndef MYLIBRARY_H_INCLUDED
#define MYLIBRARY_H_INCLUDED
#include "mainMenu.h"

///INCLUDES
#include <iostream>
#include <windows.h>
#include <math.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/freeglut.h>
#include <cmath>
#include <sstream>
#include <iomanip>

///DEFINES
#define c_red 1, 0, 0
#define c_green 0, 1, 0
#define c_blue 0, 0, 1
#define c_black 0, 0, 0
#define c_white 1, 1, 1
#define c_gray 0.5, 0.5, 0.5
#define c_grey c_gray
#define c_orange 1, 0.5, 0
#define c_yellow 1, 1, 0
#define c_purple 1, 0, 1
#define PI 3.14159265359
#define screenWidth room_width
#define screenHeight room_height
#define draw_set_color glColor3f
///FONTS
#define font_roman_stroke GLUT_STROKE_ROMAN
#define font_roman_stroke_mono GLUT_STROKE_MONO_ROMAN
#define font8_13 GLUT_BITMAP_8_BY_13
#define font9_15 GLUT_BITMAP_9_BY_15
#define font_helvetica_10 GLUT_BITMAP_HELVETICA_10
#define font_helvetica_12 GLUT_BITMAP_HELVETICA_12
#define font_helvetica_18 GLUT_BITMAP_HELVETICA_18
#define font_roman_10 GLUT_BITMAP_TIMES_ROMAN_10
#define font_roman_24 GLUT_BITMAP_TIMES_ROMAN_24

using namespace std;

///GLOBALS
static char FONT_ALIGNMENT = 'l';
static bool help = 1;
static int room_width = 640;
static int room_height = 480;

///ENUMERATORS
enum keys
{
    MOUSE_LEFT = 0,
    MOUSE_MIDDLE,
    MOUSE_RIGHT,
    MOUSE_WHEEL_UP,
    MOUSE_WHEEL_DOWN,
    KEY_F1 = 1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_ESC = 27,
    ARROW_LEFT = 100,
    ARROW_UP,
    ARROW_RIGHT,
    ARROW_DOWN,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_INSERT
};

enum rooms
{
    ROOM_MAINMENU = 0,
    ROOM_CIRCLES,
    ROOM_BEZIER,
    ROOM_CLIP,
    ROOM_TWEEN,
    ROOM_REFLECT,
    ROOM_MIRROR
};

enum alignments
{
    fa_left = 0,
    fa_right,
    fa_center
};

///OBJECTS
class point
{
public:
    float x, y;
    double r, a;
    bool placed = 0;
    operator bool() {return placed;}
    void set(int x, int y) {point::x = x; point::y = y; placed = 1;}
};

class vector
{
public:
    double magnitude, angle;
    operator float() {return magnitude;}
    operator double() {return magnitude;}
    void operator=(int a) {magnitude = double(a);}
    void operator=(float a) {magnitude = a;}
    void operator=(double a) {magnitude = a;}
};

class rectangle
{
public:
    int x1, x2, y1, y2;
    bool inside(int, int);
    bool inside(point p) {return inside(p.x, p.y);}
    void set(int x1, int x2, int y1, int y2) {rectangle::x1 = x1; rectangle::x2 = x2; rectangle::y1 = y1; rectangle::y2 = y2;}
};

class button: public rectangle
{
public:
    int room = ROOM_MAINMENU;
    bool over = 0;
    std::string text = "";
};



///FUNCTIONS
namespace myMath
{
    double distance(float x1, float x2, float y1, float y2);
    double distance(point, point);
}
void draw(point);
void draw(rectangle, bool = 0);
void draw(button, bool = 0);
void draw_circle(int x, int y, double r);
void draw_GUI();
void drawGUI(const bool, const char* = "NONAME", const char* = "", const char* = "");
void draw_GUI(const char*, const char*, const char*);

void globalSpecial(int, bool&);
void glSetWindow(int a, int b, int c, int d);
void roomPointer(void (*display)(void), void (*mouse)(int , int , int , int), void (*keyboard)(unsigned char, int, int), void (*special)(int, int, int), void (*passive)(int, int), std::string title);
bool between(double x, double x1, double x2);
void draw_set_halign(int align);
void draw_text(const char* text, int x, int y, void* font);
void draw_text(const char* text, int x, int y, void* font, float r, float g, float b, float a = 1);
void myInit();


#endif // MYLIBRARY_H_INCLUDED
