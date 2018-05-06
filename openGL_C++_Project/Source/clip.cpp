#include "clip.h"

point rect[2], line[2], clip[2];

bool in(bool *x, bool *z)
{
    bool b1 = 0, b2 = 1;
    for (int i = 0; i < 4; i++)
    {
        if (x[i]!= 0 || z[i]!=0)
        {
            b1 = 1;
            break;
        }

        if (x[i] && z[i])
        {
            b2 = 0;
            break;
        }

    }
    if (!b1 || !b2)
        return 0;
    return 1;


}

void cohen(point p, point r[], bool b[])
{
    for (int i = 0; i < 4; i++)
        b[i] = 0;
    if (p.x < min(r[0].x, r[1].x))
        b[0] = 1;
    if (p.y > max(r[0].y, r[1].y))
        b[1] = 1;
    if (p.x > max(r[0].x, r[1].x))
        b[2] = 1;
    if (p.y < min(r[0].y, r[1].y))
        b[3] = 1;

}

void clipDisplay()
{
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_set_color(c_red);
    rectangle r;
    if (rect[1])
    {
        r.set(rect[0].x, rect[1].x, rect[0].y, rect[1].y);
        draw(r, 1);

        glBegin(GL_POINTS);
        glVertex2i(rect[0].x, rect[0].y);
        glVertex2i(rect[1].x, rect[0].y);
        glVertex2i(rect[1].x, rect[1].y);
        glVertex2i(rect[0].x, rect[1].y);
        glEnd();
    }
    else if (rect[0])
    {
        glBegin(GL_POINTS);
        draw(rect[0]);
        glEnd();
    }

    if (line[0])
        draw_set_color(c_blue);
    else draw_set_color(c_black);
    draw_text("Point1: ", 0, 10, font_helvetica_12);
    if (line[1])
        draw_set_color(c_blue);
    else draw_set_color(c_black);
    draw_text("Point2: ", room_width-126, 10, font_helvetica_12);
    draw_set_color(c_black);
    for (int i = 0; i < 4; i++)
    {
        rectangle r;
        int x1 = 41 + 20*i;
        int x2 = 61 + 20*i;
        int y1 = 5;
        int y2 = 25;
        r.set(x1, x2, y1, y2);
        draw(r, 1);
        x1 = room_width-65 + 20*i;
        x2 = room_width-65-20 + 20*i;
        y1 = 5;
        y2 = 25;
        r.set(x1, x2, y1, y2);
        draw(r, 1);
    }

    draw_set_color(c_blue);
    if (line[1])
    {
        bool x[4], z[4];
        cohen(line[0], rect, x);
        for (int i = 0; i < 4; i++)
        {
            string c;
            if (x[i])
                c = 'T';
            else c = 'F';
            draw_text(c.c_str(), 47 + 20*i, 10, font_helvetica_12, c_black, 1);
        }
        cohen(line[1], rect, z);
        for (int i = 0; i < 4; i++)
        {
            string c;
            if (z[i])
                c = 'T';
            else c = 'F';
            draw_text(c.c_str(), room_width-65-20+6 + 20*i, 10, font_helvetica_12, c_black, 1);
        }

        draw_set_color(c_blue);
        //glBegin(GL_LINES);
        //glVertex2i(line[0].x, line[0].y);
        //glVertex2i(line[1].x, line[1].y);
        //glEnd();
        glBegin(GL_POINTS);
        glVertex2i(line[0].x, line[0].y);
        glVertex2i(line[1].x, line[1].y);
        glEnd();

        ///INTERSECTION
        point *p, *p2;
        if (line[0].x > line[1].x)
        {
            p = &line[1];
            p2 = &line[0];
        }
        else
        {
            p = &line[0];
            p2 = &line[1];
        }
        double m = (line[1].y - line[0].y)/(line[1].x-line[0].x);
        glBegin(GL_LINE_STRIP);
        for (double i = p->x; i <= p2->x; i++)
        {
            int y = m*(i-p->x)+p->y;
            if (r.inside(i, y))
            {
                draw_set_color(c_green);
            }
            else draw_set_color(c_blue);
                glVertex2i(i, y);



        }
        glEnd();
    }
    else if (line[0])
    {
        bool x[4];
        cohen(line[0], rect, x);
        for (int i = 0; i < 4; i++)
        {
            string c;
            if (x[i])
                c = 'T';
            else c = 'F';
            draw_text(c.c_str(), 47 + 20*i, 10, font_helvetica_12, c_black, 1);
        }
        draw_set_color(c_blue);
        glBegin(GL_POINTS);
        glVertex2i(line[0].x, line[0].y);
        glEnd();
    }




    drawGUI(help, "Dynamic Line Clipping", "Apply the Cohen-Sutherland Algorithm", "Left Click: Place Point. Right Click: Erase Last Object. Mouse Wheel: Zoom");
    glFlush();
}
inline void realclipMouse(int button, bool pressed, int x, int y)
{
    if (pressed)
    {
        switch(button)
        {
        case MOUSE_LEFT:
            if (!rect[0])
            {
                rect[0].set(x, y);
                cout<<"Placed Rectangle Point 1 at ("<<x<<", "<<y<<")"<<endl;
            }
            else if (!rect[1])
            {
                rect[1].set(x, y);
                cout<<"Placed Rectangle Point 2 at ("<<x<<", "<<y<<")"<<endl;
            }
            else if (!line[0])
            {
                line[0].set(x, y);
                cout<<"Placed Line Point 1 at ("<<x<<", "<<y<<")"<<endl;
            }
            else if (!line[1])
            {
                line[1].set(x, y);
                cout<<"Placed Line Point 2 at ("<<x<<", "<<y<<")"<<endl;
            }
            else
            {
                cout<<"Maximum Points Placed"<<endl;
            }
            break;
        case MOUSE_RIGHT:
            if (line[0])
            {
                line[0].placed = line[1].placed = 0;
                cout<<"Cleared Line."<<endl;
            }
            else if (rect[0])
            {
                rect[0].placed = rect[1].placed = 0;
                cout<<"Cleared Rectangle."<<endl;
            }
            break;
        case MOUSE_WHEEL_UP:
            {
                point mid;
                mid.set((rect[1].x + rect[0].x)/2, (rect[1].y + rect[2].y)/2);
                double distance;
                distance = rect[0].x - mid.x;
                distance *= 1.01;
                cout<<distance<<endl;
                rect[0].x = mid.x + distance;
                distance = rect[1].x - mid.x;
                distance *= 1.01;
                rect[1].x = mid.x + distance;
                distance = rect[0].y - mid.y;
                distance *= 1.01;
                rect[0].y = mid.y + distance;
                distance = rect[1].y - mid.y;
                distance *= 1.01;
                rect[1].y = mid.y + distance;
                glutPostRedisplay();
            }

            ///ZOOM code here
            break;
        case MOUSE_WHEEL_DOWN:
            {
                point mid;
                mid.set((rect[1].x + rect[0].x)/2, (rect[1].y + rect[2].y)/2);
                double distance;
                distance = rect[0].x - mid.x;
                distance /= 1.01;
                rect[0].x = mid.x + distance;
                distance = rect[1].x - mid.x;
                distance /= 1.01;
                rect[1].x = mid.x + distance;
                distance = rect[0].y - mid.y;
                distance /= 1.01;
                rect[0].y = mid.y + distance;
                distance = rect[1].y - mid.y;
                distance /= 1.01;
                rect[1].y = mid.y + distance;
                glutPostRedisplay();
            }
            break;
        }
    }
}
void clipMouse(int button, int pressed, int x, int y)
{
   realclipMouse(button, !pressed, x, room_height - y);
}
void clipMotion(int x, int y)
{
    y = room_height - y;
}
void clipKeyboard(unsigned char, int, int)
{

}

void clipSpecial(int button, int, int)
{
    globalSpecial(button, help);
}
void clipPassive(int, int)
{

}
