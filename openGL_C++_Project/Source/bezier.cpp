#include "bezier.h"

point bezier[100];
int bezPoints = -1;
int selected = -1;

point castel(int r, int i, double t)
{
    if (r < 1)
        return bezier[i];
    point p1 = castel(r-1, i, t);
    point p2 = castel(r-1, i + 1, t);
    point p3;
    p3.set((1-t)*p1.x + t* p2.x, (1-t)*p1.y + t * p2.y);
    return p3;
}

void bezierDisplay()
{
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(8.0);
    draw_set_color(c_black);
    glBegin(GL_LINE_STRIP);
    if (bezPoints > 0)
        for (double t = 0; t <= 1; t+=0.001)
        {
            point bezP = castel(bezPoints, 0, t);
            glVertex2i(bezP.x, bezP.y);
        }
    glEnd();

    glLineWidth(2.0);
    draw_set_color(c_blue);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++)
    {
        if (selected == i)
        draw_set_color(c_orange);
        if (bezier[i])
            draw(bezier[i]);
        if (selected == i)
        draw_set_color(c_blue);
    }
    glEnd();

    drawGUI(help, "Dynamic Bezier Curve", "Draw a bezier curve of up to 100 points (if your PC can handle it)", "Left Mouse: Place Point. Right Mouse: Clear Last Point, or Point under mouse. Middle Mouse: Clear All Points. Drag: Move Point.");
    glFlush();
}

inline void realbezierMouse(int button, bool pressed, int x, int y)
{
    selected = -1;
    if (pressed)
    {
        switch(button)
        {
        case MOUSE_LEFT:
            for (int i = 0; i < 100; i++)
            {
                if (!bezier[i])
                    break;
                if (bezier[i].x >= x -4 && bezier[i].x <= x + 4 && bezier[i].y >= y - 4 && bezier[i].y <= y + 4) ///Threshold of 4
                {
                    selected = i;
                }
            }
            if (selected == -1)
            for (int i = 0; i < 100; i++)
            {
                if (!bezier[i]) ///AUTO FIND FREE SLOT
                {
                    bezier[i].set(x, y);
                    bezier[i].placed = 1;
                    cout<<"Placed Bezier Point #"<<i+1<<" at ("<<bezier[i].x<<", "<<bezier[i].y<<")"<<endl;
                    bezPoints = i;
                    break;
                }

                if (i == 99)
                    cout<<"MAX LIMIT REACHED"<<endl;
            }
            else
            {

            }
            break;
        case MOUSE_RIGHT:
            for (int i = 0; i < 100; i++)
            {
                if (!bezier[i])
                    break;
                if (bezier[i].x >= x -4 && bezier[i].x <= x + 4 && bezier[i].y >= y - 4 && bezier[i].y <= y + 4) ///Threshold of 4
                {
                    selected = i;
                    for (int i = selected; i < 100; i++)
                    {
                        if (bezier[i+1])
                        {
                            bezier[i] = bezier[i+1]; ///SHIFTING
                            bezier[i+1].placed = 0;
                        }
                        else if (i == selected && !bezier[i+1]) ///Last Point
                        {
                            bezier[i].placed = 0;
                        }
                    }
                    cout<<"Cleared Point #"<<selected+1<<endl;
                    bezPoints--;
                    if (bezPoints < -1)
                        bezPoints = -1;
                }



            }
            if (selected == -1)
            {
                int i;
                for (i = 0; i < 100; i++)
                {
                    if (!bezier[i])
                    {
                        break;
                    }
                }
                bezier[i-1].placed = 0;
                bezPoints--;
                if (bezPoints < -1)
                    bezPoints = -1;
                if (i)
                    cout<<"Cleared Point #"<<i<<endl;
            }
            selected = -1;
            break;
        case MOUSE_MIDDLE:
            for (int i = 0; i < 100; i++)
            {
                bezier[i].placed = 0;
            }
            bezPoints = -1;
            cout<<"Cleared All Points."<<endl;
            break;

        }
    }
    else {}
}

void bezierMouse(int button, int pressed, int x, int y)
{
    realbezierMouse(button, !pressed, x, room_height - y);
}

void bezierKeyboard(unsigned char, int, int)
{

}

void bezierSpecial(int button, int, int)
{
    globalSpecial(button, help);
}

void bezierMotion(int x, int y)
{
    if (selected > -1)
    {
        bezier[selected].set(x, room_height - y);
        glutPostRedisplay();
    }
}

void bezierPassive(int, int)
{

}
