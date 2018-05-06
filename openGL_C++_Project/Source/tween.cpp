#include "tween.h"
#define points 10

point s1[10], s2[10], s3[10];
bool animate = 0;
int windows[3] = {2, 3, 1};


void tweenDisplay()
{
    windows[2] = glutGetWindow();
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);


    draw_set_color(c_purple);
    glBegin(GL_POLYGON);
    for (int i = 0; i < points; i++)
    {
        if (s1[i])
        {
            //if (!animate)
                //s3[i].set(s1[i].x, s1[i].y);
            glVertex2i(s3[i].x, s3[i].y);
        }

        else break;
    }
    glEnd();
    glBegin(GL_POINTS);
    for (int i = 0; i < points; i++)
    {
        if (s1[i])
        {
            //if (!animate)
                //s3[i].set(s1[i].x, s1[i].y);
            glVertex2i(s3[i].x, s3[i].y);
        }

        else break;
    }
    glEnd();


    ///ANIMATION
    if (animate)
    {
        for (int i = 0; i < points; i++)
        {
            if (!s3[i] || !s2[i])
                break;
            if (s3[i].x < s2[i].x)
                s3[i].x++;
            if (s3[i].x > s2[i].x)
                s3[i].x--;
            if (s3[i].y > s2[i].y)
                s3[i].y--;
            if (s3[i].y < s2[i].y)
                s3[i].y++;
            glutPostRedisplay();
        }
    }


    draw_set_color(c_black);
    stringstream ani;
    ani<<"Animation Status: "<<animate;
    draw_text(ani.str().c_str(), 5, 10, font_helvetica_12);
    drawGUI(help, "Tweening Animation", "MAKE SURE BOTH WINDOWS HAVE SAME NUMBER OF POINTS", "Press Space to toggle Animation. Left Click: Reset All");
    glFlush();
}
void tweenDisplay2()
{
    windows[0] = glutGetWindow();
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_set_color(c_red);

    glBegin(GL_POLYGON);
    for (int i = 0; i < points; i++)
    {
        //cout<<s1[i].x<<" "<<s1[i].y<<endl;
        if (s1[i])
            glVertex2i(s1[i].x, s1[i].y);
        else break;
    }
    glEnd();
    glBegin(GL_POINTS);
    for (int i = 0; i < points; i++)
    {
        if (s1[i])
            glVertex2i(s1[i].x, s1[i].y);
        else break;
    }
    glEnd();

    drawGUI(help, "Shape 1", "Draw you first shape here.");
    glFlush();
}
void tweenDisplay3()
{
    windows[1] = glutGetWindow();
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_set_color(c_blue);

    glBegin(GL_POLYGON);
    for (int i = 0; i < points; i++)
    {
        if (s2[i])
            glVertex2i(s2[i].x, s2[i].y);
        else
            break;
    }
    glEnd();
    glBegin(GL_POINTS);
    for (int i = 0; i < points; i++)
    {
        if (s2[i])
            glVertex2i(s2[i].x, s2[i].y);
        else
            break;
    }
    glEnd();

    drawGUI(help, "Shape 2", "Draw you second shape here.");
    glFlush();
}

inline void realtweenMouse(int button, bool pressed, int x, int y)
{
    int window = glutGetWindow();
    glutSetWindow(windows[2]);
    glutPostRedisplay();
    //glutSetWindow(windows[1]);
    //glutPostRedisplay();
    glutSetWindow(window);
    if (button == MOUSE_RIGHT && pressed && (window == windows[0] || window == windows[2]))
    {
        glutSetWindow(windows[0]);
        glutPostRedisplay();
        for (int i = 0; i < points; i++)
        {
            s1[i].placed = s3[i].placed = 0;
        }
        cout<<"Cleared all Points in Rooms 1 & 2"<<endl;
    }
    if (window == windows[0])
    {
        if (button == MOUSE_LEFT && pressed)
        {
            for (int i = 0; i < points; i++)
            {
                if (!s1[i])
                {
                    s1[i].set(x, y);
                    s3[i].set(x, y);
                    cout<<"Point #"<<i+1<<" in room "<<window<<" placed at ("<<x<<", "<<y<<")"<<endl;
                    break;
                }
                if (i == points - 1)
                    cout<<"MAX LIMIT REACHED"<<endl;
            }
        }
    }
    else if (window == windows[1])
    {
        if (button == MOUSE_LEFT && pressed)
        {
            for (int i = 0; i < points; i++)
            {
                if (!s2[i])
                {
                    s2[i].set(x, y);
                    cout<<"Point #"<<i+1<<" in room "<<window<<" placed at ("<<x<<", "<<y<<")"<<endl;
                    break;
                }
                if (i == points - 1)
                    cout<<"MAX LIMIT REACHED"<<endl;
            }
        }
        if (button == MOUSE_RIGHT && pressed)
        {
            for (int i = 0; i < points; i++)
            {
                s2[i].placed = 0;
            }
            cout<<"Cleared all Points in Room 3"<<endl;
        }
    }

}
void tweenMouse(int button, int pressed, int x, int y)
{
    realtweenMouse(button, !pressed, x, room_height - y);
}
void tweenKeyboard(unsigned char key, int, int)
{
    if (key == 0x20)
    {
        animate = !animate;
        glutSetWindow(windows[2]);
        glutPostRedisplay();
    }

}
void tweenSpecial(int button, int, int)
{
    if (button == KEY_HOME)
    {

        glutDestroyWindow(windows[0]);
        glutDestroyWindow(windows[1]);

        glutSetWindow(windows[2]);

    }
    globalSpecial(button, help);
    for (int i = 0; i < 2; i++)
    {
        glutSetWindow(windows[i]);
        glutPostRedisplay();
    }
}
void tweenPassive(int, int)
{

}
