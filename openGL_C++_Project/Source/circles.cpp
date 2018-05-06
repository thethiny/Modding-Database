#include "circles.h"

point p1[4], p2[4]; ///3 Points + Center
point intersect[2];
vector r1, r2;
//bool help = 1;

void circleDisplay()
{
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);


    draw_set_color(c_red);
    for (int i = 0; i < 4; i++)
        if (p1[i])
            draw(p1[i]);

    if (p1[3])
    {
        draw_circle(p1[3].x, p1[3].y, float(r1));
    }

    draw_set_color(c_green);
    for (int i = 0; i < 4; i++)
    {
        if (p2[i])
            draw(p2[i]);
    }

    if (p2[3])
    {
        draw_circle(p2[3].x, p2[3].y, float(r2));
    }

    ///INTERSECTIONS
    draw_set_color(c_blue);
    double d = myMath::distance(p1[3], p2[3]);
    double a;
    if ( d <= float(r1) + float(r2) && d >= abs(float(r1)-float(r2)) && !(d == 0 && float(r1) == float(r2)) && p2[3])
    {
        a = (pow(r1, 2.0) - pow(r2, 2.0) + pow(d, 2.0))/ (2*d);
        double h = sqrt(pow(r1, 2.0) - pow(a, 2.0));
        double x1 = p1[3].x + a*(p2[3].x - p1[3].x)/d;
        double y1 = p1[3].y + a*(p2[3].y - p1[3].y)/d;
        intersect[0].set(x1 - h*(p2[3].y - p1[3].y)/d, y1 + h*(p2[3].x - p1[3].x)/d);
        intersect[1].set(x1 + h*(p2[3].y - p1[3].y)/d, y1 - h*(p2[3].x - p1[3].x)/d);
        for (int i = 0; i < 2; i++)
            draw(intersect[i]);
    }


    //cout<<"D: "<<d<<endl<<"R1 + R2: "<<float(r1)+float(r2)<<endl<<"R1: "<<float(r1)<<endl<<"R2: "<<float(r2)<<endl;

//intersect[0].set(p1[3].x + h*(p2[3].x - p1[3].x)/d, p1[3].y + h*(p2[3].y - p1[3].y)/d);



    drawGUI(help, "Animating Circles", "Place 3 points to place a circle (Twice) to calculate their intersection points.", "Left Click: Place Point. Right Click: Erase Circle. WASD: Move Circle 1. Arrow Keys: Move Circle 2.");
    glFlush();
}

inline void clear(int a = 0)
{
    if (a)
    {
        for (int i = 0; i < 4; i++)
        {
            p1[i].placed = p2[i].placed = intersect[i%2].placed = 0;
        }
    }
    else
    for (int i = 0; i < 4; i++)
    {
        if (p2[0])
            p2[3-i].placed = 0;
        else if (p1[0])
        {
            p1[3-i].placed = 0;
        }
    }
    intersect[0].placed = intersect[1].placed = 0;
    cout<<"Cleared Last Circle."<<endl;
}

inline void realCircleMouse(int button, bool pressed, int x, int y)
{
    if (button == MOUSE_LEFT && pressed)
    {
        if (!p1[0])
        {
            p1[0].set(x, y);
            cout<<"Point 1 at ("<<x<<", "<<y<<")"<<endl;
        }
        else if (!p1[1])
        {
            p1[1].set(x, y);
            cout<<"Point 2 at ("<<x<<", "<<y<<")"<<endl;
        }
        else if (!p1[2])
        {
            p1[2].set(x, y);
            cout<<"Point 3 at ("<<x<<", "<<y<<")"<<endl;
            float ma = (p1[1].y - p1[0].y)/(p1[1].x-p1[0].x);
            float mb = (p1[2].y - p1[1].y)/(p1[2].x-p1[1].x);
            p1[3].x = (ma*mb*(p1[0].y-p1[2].y)+mb*(p1[0].x+p1[1].x)-ma*(p1[1].x+p1[2].x))/(2*(mb-ma));
            if (isnan(p1[3].x))
            {
                cout<<"INVALID CIRCLE! RESETTING\n";
                p1[0].placed = 0;
                p1[1].placed = 0;
                p1[2].placed = 0;
            }
            else
            {
                p1[3].y = - (1/ma)*(p1[3].x - ((p1[0].x+p1[1].x)/2))+((p1[0].y+p1[1].y)/2);
                p1[3].placed = 1;
                r1 = double(myMath::distance(p1[0], p1[3]));
                cout<<"Center of Circle 1 at ("<<p1[3].x<<", "<<p1[3].y<<")"<<endl;
                cout<<"Radius is "<<float(r1)<<endl;
            }

        }
        else if (!p2[0])
        {
            p2[0].set(x, y);
            cout<<"Point 2-1 at ("<<x<<", "<<y<<")"<<endl;
        }
        else if (!p2[1])
        {
            p2[1].set(x, y);
            cout<<"Point 2-2 at ("<<x<<", "<<y<<")"<<endl;
        }
        else if (!p2[2])
        {
            p2[2].set(x, y);
            cout<<"Point 2-3 at ("<<x<<", "<<y<<")"<<endl;
            float ma = (p2[1].y - p2[0].y)/(p2[1].x-p2[0].x);
            float mb = (p2[2].y - p2[1].y)/(p2[2].x-p2[1].x);
            p2[3].x = (ma*mb*(p2[0].y-p2[2].y)+mb*(p2[0].x+p2[1].x)-ma*(p2[1].x+p2[2].x))/(2*(mb-ma));
            if (isnan(p2[3].x))
            {
                cout<<"INVALID CIRCLE! RESETTING\n";
                p2[0].placed = 0;
                p2[1].placed = 0;
                p2[2].placed = 0;
            }
            else
            {
                p2[3].y = - (1/ma)*(p2[3].x - ((p2[0].x+p2[1].x)/2))+((p2[0].y+p2[1].y)/2);
                p2[3].placed = 1;
                r2 = myMath::distance(p2[3], p2[0]);//sqrt(pow(p2[0].x-p2[3].x, 2.0) + pow(p2[0].y-p2[3].y, 2.0));
                cout<<"Center of Circle 1 at ("<<p2[3].x<<", "<<p2[3].y<<")"<<endl;
                cout<<"Radius is "<<float(r2)<<endl;
            }

        }
        else
        {
            cout<<"2 Circles have been drawn. Right Click to erase one circle."<<endl;
        }
    }
    else if (button == MOUSE_RIGHT && pressed)
    {
        clear();
    }
}

void circleMouse(int button, int pressed, int x, int y)
{
    realCircleMouse(button, !pressed, x, room_height - y);
}
void circleKeyboard(unsigned char key, int x, int y)
{
    key = tolower(key);
    switch(key)
    {
    case 'a':
        for (int i = 0; i < 4; i++)
            p1[i].x -= 2;
        break;
    case 'd':
        for (int i = 0; i < 4; i++)
            p1[i].x += 2;
        break;
    case 'w':
        for (int i = 0; i < 4; i++)
            p1[i].y += 2;
        break;
    case 's':
        for (int i = 0; i < 4; i++)
            p1[i].y -= 2;
        break;
    //case char(8):
        //clear(1);
        //room_goto(ROOM_MAINMENU);
        //break;
    }
    glutPostRedisplay();
}

void circleSpecial(int button, int x, int y)
{
    switch(button)
    {
    case ARROW_LEFT:
        for (int i = 0; i < 4; i++)
        {
            p2[i].x -= 2;
        }
        break;
    case ARROW_RIGHT:
        for (int i = 0; i < 4; i++)
        {
            p2[i].x += 2;
        }
        break;
    case ARROW_UP:
        for (int i = 0; i < 4; i++)
        {
            p2[i].y += 2;
        }
        break;
    case ARROW_DOWN:
        for (int i = 0; i < 4; i++)
        {
            p2[i].y -= 2;
        }
        break;
    }

    globalSpecial(button, help);
}

void circlePassive(int x, int y)
{
    y = room_height - y;
}

