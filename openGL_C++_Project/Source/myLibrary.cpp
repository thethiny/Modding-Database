#include "myLibrary.h"

///OBJECT FUNCTIONS

void draw(point a)
{
    glBegin(GL_POINTS);
    glVertex2f(a.x, a.y);
    glEnd();
}

void draw(button b, bool outline)
{
    draw(rectangle(b), outline);

        if (b.over)
            draw_set_color(c_black);
        else draw_set_color(c_white);
    int x = (b.x1+b.x2)/2;
    int y = (b.y1+b.y2)/2;
    glRasterPos2f(x-b.text.length()*4, y-6.5); ///4 is 8/2, 6.5 is 13/2
    glutBitmapString(font8_13, (unsigned char*)(b.text.c_str()));
}

void draw(rectangle b, bool outline)
{
    if (outline)
        glBegin(GL_LINE_LOOP);
    else glBegin(GL_POLYGON);
    glVertex2i(b.x1, b.y1);
    glVertex2i(b.x2, b.y1);
    glVertex2i(b.x2, b.y2);
    glVertex2i(b.x1, b.y2);
    glEnd();
}

bool rectangle::inside(int x, int y)
{
    if (x >= min(x1, x2) && x <= max(x1, x2) && y >= min(y1, y2) && y <= max(y1,y2))
        return 1;
    return 0;
}

void draw_circle(int x, int y, double r)
{
    glBegin(GL_LINE_LOOP);
    for (float t = 0; t < 1; t+=0.01)
    {
        glVertex2d(x + r*cos(2*PI*t), y + r*sin(2*PI*t));
    }
    glEnd();
}
void drawGUI(const bool help, const char *t1, const char *t2, const char *t3)
{
    if (help)
        draw_GUI(t1, t2, t3);
    else
    {
        draw_set_color(c_black);
        draw_set_halign(fa_left);
        draw_text("F1: Toggle HUD. Home: Menu", room_width - 170, room_height -10, font_helvetica_10);
    }
    //glutPostRedisplay();
}

void draw_GUI()
{
    glBegin(GL_POLYGON);
    draw_set_color(1, 0.4, 0.4);
    glVertex2f(0, room_height);
    glVertex2f(room_width, room_height);
    draw_set_color(1, 0.1, 0.1);
    glVertex2f(room_width, room_height*0.82);
    glVertex2f(0, room_height*0.82);
    glEnd();

    draw_set_color(c_black);

    glBegin(GL_LINES);
    glVertex2f(0, room_height*0.82);
    glVertex2f(room_width, room_height*0.82);
    glEnd();
}

void draw_GUI(const char *t1, const char *t2, const char *t3)
{
    glBegin(GL_POLYGON);
    draw_set_color(1, 0.4, 0.4);
    glVertex2f(0, room_height);
    glVertex2f(room_width, room_height);
    draw_set_color(1, 0.1, 0.1);
    glVertex2f(room_width, room_height*0.82);
    glVertex2f(0, room_height*0.82);
    glEnd();

    draw_set_color(c_white);

    draw_set_halign(fa_left);
    draw_text(t1, 10, room_height*0.95, font_roman_24);
    draw_text(t2, 10, room_height*0.9, font_helvetica_12);
    draw_text(t3, 10, room_height*0.85, font_helvetica_10);

    draw_set_color(c_black);

    glBegin(GL_LINES);
    glVertex2f(0, room_height*0.82);
    glVertex2f(room_width, room_height*0.82);

    glEnd();

    draw_set_color(c_white);
    draw_text("F1: Toggle HUD. Home: Menu", room_width - 170, room_height -10, font_helvetica_10);
}
double myMath::distance(float x1, float x2, float y1, float y2)
{
    return sqrt(pow(x1-x2, 2.0) + pow(y1-y2, 2.0));
}

double myMath::distance(point p1, point p2)
{
    return sqrt(pow(p1.x-p2.x, 2.0) + pow(p1.y-p2.y, 2.0));
}



///FUNCTIONS
void globalSpecial(const int button, bool &help)
{
    switch(button)
    {
    case KEY_F1:
        help = !help;
        break;
    case KEY_HOME:
        room_goto(ROOM_MAINMENU);
        break;
    }

    glutPostRedisplay();
}
void glSetWindow(int left, int right, int bottom, int top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}
void roomPointer(void (*display)(void), void (*mouse)(int , int , int , int), void (*keyboard)(unsigned char, int, int), void (*special)(int, int, int), void (*passive)(int, int), string title)
{
    ///RESET VIEWS
    glSetWindow(0, room_width, 0, room_height);
    glViewport(0, 0, room_width, room_height);
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    //glutMotionFunc(motion);
    glutPassiveMotionFunc(passive);
    glutSetWindowTitle(title.c_str());


    cout<<"Switching to Room: " + title<<endl;
    myInit();
    help = 1;
}

bool between(double x, double x1, double x2)
{
    double *p1, *p2;
    if (x1 > x2)
    {
        p1 = &x1;
        p2 = &x2;
    }
    else
    {
        p1 = &x2;
        p2 = &x1;
    }

    if (x >= *p2 && x <= *p1)
        return 1;
    return 0;
}

void draw_set_halign(int align)
{
    if (align == fa_right)
        FONT_ALIGNMENT = 'r';
    else if (align == fa_center)
        FONT_ALIGNMENT = 'c';
    else FONT_ALIGNMENT = 'l';
}

void draw_text(const char* text, int x, int y, void* font)
{
    switch(FONT_ALIGNMENT)
    {
    case 'l':
        glRasterPos2f(x, y);
        break;
    case 'c':
        glRasterPos2f(x-strlen(text)/2, y);
        break;
    case 'r':
        glRasterPos2f(x-strlen(text), y);

    }
    glutBitmapString(font, (unsigned char*)(text));
}

void draw_text(const char* text, int x, int y, void* font, float r, float g, float b, float a)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(r, g, b, a);
    draw_text(text, x, y, font);
    glDisable(GL_BLEND);
}

void myInit()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glLineWidth(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, room_width, 0.0, room_height);
}
