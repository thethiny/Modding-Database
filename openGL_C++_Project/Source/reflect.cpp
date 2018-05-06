#include "reflect.h"

point mirror[2];
vector reflect;

struct light
{
    point p;
    vector v;
    int size;
    void draw()
    {
        glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        ///Light
        glBegin(GL_POLYGON);
        for (double t = 0; t <= 1; t += 0.1)
        {
            glColor4f(c_yellow, cos(2*PI*t));
            double r = size*4;
            double x = p.x+5 + r*cos(2*PI*t);
            double y = p.y + r*sin(2*PI*t);
            glVertex2d(x, y);
        }
        glEnd();
        ///AMMA FIRIN MAH LAZERRRRR
        glLineWidth(4.0);
        //v.magnitude = room_width - p.x;
        draw_set_color(c_yellow);
        glBegin(GL_LINES);
        glVertex2i(p.x + 25, p.y);
        glVertex2i(p.x + v.magnitude, p.y + v.magnitude*sin(v.angle));
        glEnd();
        glLineWidth(1.0);
        ///Yellow Inside
        //draw_set_color(c_yellow);
        glBegin(GL_POLYGON);
        for (double t = 0; t <= 1; t += 0.1)
        {
            double r = size;
            double x = p.x+size + r*cos(2*PI*t)*2;
            double y = p.y + r*sin(2*PI*t);
            glVertex2d(x, y);
        }
        glEnd();
        ///Holder
        draw_set_color(c_gray);
        glBegin(GL_POLYGON);
        for (double t = 0; t <= 1; t += 0.1)
        {
            double r = size;
            double x = p.x+size-5 + r*cos(2*PI*t);
            double y = p.y + r*sin(2*PI*t);
            glVertex2d(x, y);
        }
        glEnd();
        ///Light Source
        draw_set_color(c_orange);
        glBegin(GL_POLYGON);
        for (double t = 0; t <= 1; t += 0.1)
        {
            double r = size;
            double x = p.x+size + r*cos(2*PI*t);
            double y = p.y + r*sin(2*PI*t)*0.8;
            glVertex2d(x, y);
        }
        glEnd();
        ///Holder Part 2
        draw_set_color(c_gray);
        glRecti(p.x-size*2, p.y-(0.5*size), p.x+size, p.y+(0.5*size));

    }
    light();
    light(int x, int y, int size = 10)
    {
        p.x = x;
        p.y = y;
        light::size = size;
        v.angle = 0;
    }
    light(point p, int size = 10)
    {
        light::p = p;
        light::size = size;
    }
    operator bool()
    {
        return bool(p);
    }
};

light obj(100, 100);

void reflectDisplay()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (mirror[0])
    {
        obj.v.magnitude = mirror[0].x - obj.p.x;
        glLineWidth(4.0);
        draw_set_color(c_yellow);
        glBegin(GL_LINES);
        glVertex2i(mirror[0].x, obj.p.y + obj.v.magnitude*sin(obj.v.angle));
        glVertex2i(0, (obj.p.y + obj.v.magnitude*sin(obj.v.angle)) + obj.v.magnitude*sin(obj.v.angle));
        glEnd();

        glLineWidth(2.0);
        glBegin(GL_LINES);
        draw_set_color(c_white);
        glVertex2i(mirror[0].x, 0);
        glVertex2i(mirror[0].x, room_height);
        draw_set_color(c_gray);
        glVertex2i(mirror[0].x+2, 0);
        glVertex2i(mirror[0].x+2, room_height);
        glEnd();
        draw_set_color(c_white);
        glLineWidth(1.0);
    }
    else
    {
        obj.v.magnitude = room_width;
    }





    obj.draw();


    drawGUI(help, "Dynamic Reflections", "Simulate light's reflection on a mirror.", "WASD: Move Light. Shift + WASD: Move Light x2 Speed. Left Mouse: Move Mirror. Right Click: Erase. Arrows: Light Rotation");
    glFlush();
}
inline void realreflectMouse(int button, bool pressed, int x, int y)
{
    if (MOUSE_LEFT == button && pressed)
    {
        mirror[0].set(x, y);
        if (obj.p.x > mirror[0].x-30)
            obj.p.x = mirror[0].x-30;
        if (!mirror[0])
        {
            cout<<"Mirror Placed at X-Axis "<<x<<"."<<endl;
        }
        else
        {
            cout<<"Mirror Moved to X-Axis "<<x<<"."<<endl;
        }
    }
    else if (MOUSE_RIGHT == button && pressed)
    {
        if (mirror[0])
        {
            mirror[0].placed = 0;
        }
    }

}
void reflectMouse(int button, int pressed, int x, int y)
{
    realreflectMouse(button, !pressed, x, room_height - y);
}
void reflectMotion(int, int)
{

}
void reflectKeyboard(unsigned char key, int, int)
{
    switch(key)
    {
    case 'a':
        obj.p.x -= 2;
        break;
    case 'd':
        obj.p.x += 2;
        break;
    case 'w':
        obj.p.y += 2;
        break;
    case 's':
        obj.p.y -= 2;
        break;
    case 'A':
        obj.p.x -= 8;
        break;
    case 'D':
        obj.p.x += 8;
        break;
    case 'W':
        obj.p.y += 8;
        break;
    case 'S':
        obj.p.y -= 8;
        break;
    }
    if (obj.p.x < 0)
    {
        obj.p.x = 0;
    }
    if (obj.p.x > room_width)
    {
        obj.p.x = room_width;
    }
    if (obj.p.y > room_height)
    {
        obj.p.y = room_height;
    }
    if (obj.p.y < 0)
    {
        obj.p.y = 0;
    }
    if (mirror[0])
    {
        if (obj.p.x > mirror[0].x-30)
            obj.p.x = mirror[0].x-30;
    }
    glutPostRedisplay();
}
void reflectSpecial(int button, int, int)
{
    switch(button)
    {
    case ARROW_LEFT:
        obj.v.angle += 1* (PI/180.0);
        break;
    case ARROW_RIGHT:
        obj.v.angle -= 1* (PI/180.0);
        break;
    }
    glutPostRedisplay();
    globalSpecial(button, help);
}
void reflectPassive(int x, int y)
{

}
void reflectDrag(int x, int y)
{
    if (mirror[0])
    {
        mirror[0].set(x, room_height - y);
        if (obj.p.x > mirror[0].x-30)
            obj.p.x = mirror[0].x-30;
    }
    glutPostRedisplay();
}
