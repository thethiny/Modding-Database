#include "mirror.h"

int local_width = room_width;
int local_height = room_height;

enum colors
{
    blank,
    red,
    green,
    blue,
    yellow,
    orange,
    purple,
    white,
    black
};

int color = red, mode = 0, window;

struct node: public point
{
    int color = blank;
    int mode = 0; ///0 = point, 1 = line, 2 = line_strip, 3 = polygon
    int split = 0; ///If 1, start new line
    draw()
    {
        switch(color)
        {
        case red:
            draw_set_color(c_red);
            break;
        case green:
            draw_set_color(c_green);
            break;
        case blue:
            draw_set_color(c_blue);
            break;
        case yellow:
            draw_set_color(c_yellow);
            break;
        case orange:
            draw_set_color(c_orange);
            break;
        case purple:
            draw_set_color(c_purple);
            break;
        case white:
            draw_set_color(c_white);
            break;
        case black:
            draw_set_color(c_black);
            break;
        }

        glVertex2i(x, y);
    }
};

node p[5000];
node c[4];

void mainDraw()
{
    draw_set_color(c_red);
    //glRecti(0, local_height/2, local_width, local_height); ///Clipping
    /*glBegin(GL_POINTS);
    for (int i = 0; i < 5000; i++)
    {
        if (p[i])
        {
                p[i].draw();
        }
        else break;
    }
    glEnd();*/

    int lastmode;
    for (int i = 0; i < 5000; i++)
    {
        if (p[i])
        {
            switch(p[i].mode)
            {
            case 1:
                glBegin(GL_LINES);
                lastmode = 1;
                break;
            case 2:
                glBegin(GL_LINE_STRIP);
                lastmode = 2;
                break;
            case 3:
                glBegin(GL_POLYGON);
                lastmode = 3;
                break;
            case 4:
                glBegin(GL_LINE_LOOP);
                lastmode = 4;
                break;
            default:
                glBegin(GL_POINTS);
                lastmode = 0;
            }
            while(p[i] && p[i].mode == lastmode && !p[i].split)
            {
                p[i].draw();
                i++;
            }
            if (p[i] && p[i].mode == lastmode && p[i].split)
            {
                p[i].draw();
            }
            if (p[i].mode != lastmode)
                i--;
            glEnd();
        }
    }
    glBegin(GL_POINTS);
    for (int i = 0; i < 5000; i++)
    {
        if (p[i] && p[i].mode)
        {
                p[i].draw();
        }
        else if (p[i])
            continue;
        else break;
    }
    glEnd();


}
void mirrorDisplay2()
{
    ///RESET
    glSetWindow(0, room_width, 0, room_height);
    glViewport(0, 0, room_width, room_height);
    glPointSize(4.0);
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(16.0);
    c[0].set(room_width/4, room_height/2);
    c[0].color = color;
    c[0].mode = mode;
    c[1].set(room_width/2, room_height/4);
    c[1].color = color;
    c[1].mode = mode;
    c[2].set(room_width*0.75, room_height/2);
    c[2].color = color;
    c[2].mode = mode;
    c[3].set(room_width/2, room_height*0.75);
    c[3].color = color;
    c[3].mode = mode;
    switch(mode)
    {
    case 0:
        glBegin(GL_POINTS);
        break;
    case 1:
        glBegin(GL_LINES);
        break;
    case 2:
        glBegin(GL_LINE_STRIP);
        break;
    case 3:
        glBegin(GL_POLYGON);
        break;
    case 4:
        glBegin(GL_LINE_LOOP);
    }
    c[0].draw();
    c[1].draw();
    c[2].draw();
    c[3].draw();
    glEnd();

    glBegin(GL_POINTS);
    for (int i = 0; i < 4; i++)
        c[i].draw();
    glEnd();

    drawGUI(help, "Dynamic Mirroring", "Draw inside the Red Box. The 4 points below demo your current draw settings. Screen Resizeable.", "1-8 Draw Color. Z: Points. X: Lines. C: Line Strip. V: Line Loop. B: Polygon. Mouse R: Undo. Mouse M: Clear All. ESC: New Segment.");
    glFlush();
}
void mirrorDisplay()
{
    window = glutGetWindow();
    //glutReshapeWindow(1920, 1080);
    //local_width = 1920;
    //local_height = 1080;
    glPointSize(4.0);
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    ///The problem is here
    rectangle b[4];
    b[0].set(0, local_width/2, local_height/2, local_height);
    b[1].set(local_width/2, local_width, local_height/2, local_height);
    b[2].set(local_width/2, local_width, 0, local_height/2);
    b[3].set(0, local_width/2, 0, local_height/2);

    draw_set_color(c_black);
    for (int i = 3; i >= 0; i--)
    {
        if(i == 0)
        {
            draw_set_color(c_red);

        }
        draw(b[i], 1);
    }



    ///DRAW INSIDE
    glSetWindow(0, local_width/2, local_height/2, local_height);
    glViewport(0, local_height/2, local_width/2, local_height/2); ///Clipping not scaling
    mainDraw();

    ///Reflect TR
    glSetWindow(local_width/2, 0, local_height/2, local_height);
    glViewport(local_width/2, local_height/2, local_width/2, local_height/2);
    mainDraw();

    ///Reflect BL
    glSetWindow(0, local_width/2, local_height, local_height/2);
    glViewport(0, 0, local_width/2, local_height/2);
    mainDraw();

    ///Reflect BR
    glSetWindow(local_width/2, 0, local_height, local_height/2);
    glViewport(local_width/2, 0, local_width/2, local_height/2);
    mainDraw();





    ///RESET
    glSetWindow(0, local_width, 0, local_height);
    glViewport(0, 0, local_width, local_height);


    glFlush();
}
inline void realmirrorMouse(int button, bool pressed, int x, int y)
{
    if (MOUSE_LEFT == button && pressed)
    {
        for (int i = 0; i < 5000; i++)
        {
            if (!p[i])
            {
                if ((x >= 0 && x <= local_width/2 && y >= local_height/2 && y <= local_height && mode == 0) || mode != 0)
                {
                    p[i].set(x, y);
                    p[i].color = color;
                    p[i].mode = mode;
                    p[i].split = 0;
                    cout<<"Placed point "<<i+1<<" at ("<<x<<", "<<y<<")"<<endl;
                }
                break;
            }
        }
    }
    if (MOUSE_RIGHT == button && pressed)
    {
        int i;
        for (i = 0; i < 5000; i++)
        {
            if (!p[i])
                break;
        }
        if (i)
        {
            p[i-1].placed = 0;
            cout<<"Undo"<<endl;
        }
    }
    if (MOUSE_MIDDLE == button && pressed)
    {
        for (int i = 0; i < 5000; i++)
        {
            if (p[i])
                p[i].placed = 0;
            else break;
        }
        cout<<"Cleared all points."<<endl;
    }
}
void mirrorMouse(int a, int b, int c, int d)
{
    realmirrorMouse(a, !b, c, local_height - d);
}
void mirrorMouse2(int a, int b, int c, int d)
{

}
void mirrorMotion(int, int)
{

}
void mirrorKeyboard(unsigned char key, int, int)
{
    key = tolower(key);
    switch(key)
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
        color = key - '0';
        break;
    case 'z':
        mode = 0;
        break;
    case 'x':
        mode = 1;
        break;
    case 'c':
        mode = 2;
        break;
    case 'v':
        mode = 4;
        break;
    case 'b':
        mode = 3;
        break;
    case KEY_ESC:
        int i;
        for (i = 0; i < 5000; i++)
        {
            if (!p[i])
                break;
        }
        if (i)
            p[i-1].split = 1;
        break;
    }
    glutSetWindow(1);
    glutPostRedisplay();
    glutSetWindow(window);
    glutPostRedisplay();
}
void mirrorSpecial(int button, int, int)
{
    //globalSpecial(button, help);
    if (button == KEY_HOME)
    {
        ///Terminate Windows
        glutDestroyWindow(window);
        glutSetWindow(1);
        room_goto(ROOM_MAINMENU);
    }

}
void mirrorPassive(int, int)
{

}
void mirrorReshape(int x, int y)
{
    local_width = x;
    local_height = y;
}
