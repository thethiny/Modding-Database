#include "mainMenu.h"

#define buttonsNo 6
button b[buttonsNo];

void room_goto(int r)
{
    switch(r)
    {
    case ROOM_MAINMENU:
        roomPointer(mainMenu, mainMouse, mainKeyboard, mainSpecial, mainPassive, "Main Menu");
        break;
    case ROOM_CIRCLES:
        roomPointer(circleDisplay, circleMouse, circleKeyboard, circleSpecial, circlePassive, "Animating Circles");
        break;
    case ROOM_BEZIER:
        roomPointer(bezierDisplay, bezierMouse, bezierKeyboard, bezierSpecial, bezierPassive, "Dynamic Bezier Curve");
        glutMotionFunc(bezierMotion);
        break;
    case ROOM_CLIP:
        roomPointer(clipDisplay, clipMouse, clipKeyboard, clipSpecial, clipPassive, "Dynamic Line Clipping");
        glutMotionFunc(clipMotion);
        break;
    case ROOM_MIRROR:
        roomPointer(mirrorDisplay2, mirrorMouse2, mirrorKeyboard, mirrorSpecial, mirrorPassive, "Dynamic Mirroring");
        glutInitWindowPosition(400, 400);
        glutCreateWindow("");
        roomPointer(mirrorDisplay, mirrorMouse, mirrorKeyboard, mirrorSpecial, mirrorPassive, "Painter");
        glutReshapeFunc(mirrorReshape);
        myInit();
        break;
    case ROOM_REFLECT:
        roomPointer(reflectDisplay, reflectMouse, reflectKeyboard, reflectSpecial, reflectPassive, "Vector Reflection");
        glutMotionFunc(reflectDrag);
        break;
    case ROOM_TWEEN:
        {
        roomPointer(tweenDisplay, tweenMouse, tweenKeyboard, tweenSpecial, tweenPassive, "Tweening Animation");
        glutInitWindowPosition(200, 200);
        glutCreateWindow("");
        roomPointer(tweenDisplay2, tweenMouse, tweenKeyboard, tweenSpecial, tweenPassive, "Shape 1");
        glutInitWindowPosition(300, 300);
        glutCreateWindow("");
        roomPointer(tweenDisplay3, tweenMouse, tweenKeyboard, tweenSpecial, tweenPassive, "Shape 2");
        myInit();
        }

        break;
    default:
        cout<<"Room with ID "<<r<<" does not exist!"<<endl;
    }
}

void mainMenu()
{
    glClearColor(1, 1, 0.8, 0);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

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
    stringstream IDs;
    stringstream version;
    version<<"Computer Graphics Project v"<<"1.2.1";
    IDs<<left<<setfill(' ')<<setw(21)<<"U14110128"<<setw(19)<<"U14111348"<<setw(35)<<"U14111460"<<setw(11)<<"U14120982";
    draw_text(version.str().c_str(), 10, room_height*0.95, font_roman_24);
    draw_text("Ridhwan Al-Debsi | Elimam Mohamed | Abdullah Fahd Ba-Hemdan | Noor Ghazal", 10, room_height*0.9, font_helvetica_12);
    draw_text(IDs.str().c_str(), 10, room_height*0.85, font_helvetica_12);

    draw_set_color(c_black);

    glBegin(GL_LINES);
    glVertex2f(0, room_height*0.82);
    glVertex2f(room_width, room_height*0.82);
    glEnd();


    for (int i = 0; i < 6; i++)
    {
        stringstream ss;
        ss<<"Button "<<i+1;
        b[i].text = ss.str();
        switch(i)
        {
        case 0:
            b[i].text = "Animating Circles";
            b[i].room = ROOM_CIRCLES;
            break;
        case 1:
            b[i].text = "Tweening";
            b[i].room = ROOM_TWEEN;
            break;
        case 2:
            b[i].text = "Reflections";
            b[i].room = ROOM_REFLECT;
            break;
        case 3:
            b[i].text = "Dynamic Bezier Curve";
            b[i].room = ROOM_BEZIER;
            break;
        case 4:
            b[i].text = "Dynamic Line Clipping";
            b[i].room = ROOM_CLIP;
            break;
        case 5:
            b[i].text = "Mirroring (Painter)";
            b[i].room = ROOM_MIRROR;
            break;

        }
        b[i].x1 = (i%2)*300 + 70;
        b[i].x2 = (i%2)*300 + 270;
        b[i].y1 = (i%3)*120 + 30;
        b[i].y2 = (i%3)*120 + 130;
        if (b[i].over)
            switch(i)
            {
            case 0:
                draw_set_color(c_green);
                break;
            case 1:
                draw_set_color(c_red);
                break;
            case 2:
                draw_set_color(c_blue);
                break;
            case 3:
                draw_set_color(c_orange);
                break;
            case 4:
                draw_set_color(c_yellow);
                break;
            case 5:
                draw_set_color(c_purple);
                break;

            }

        else draw_set_color(c_gray);
        draw(b[i]);
    }


    glFlush();
}

void realMainMouse(int button, bool pressed, int x, int y)
{
    if (button == MOUSE_LEFT && pressed)
    for (int i = 0; i < buttonsNo; i++)
    {
        if (b[i].inside(x, y))
        {
            cout<<"Clicked Button "<<i+1<<endl;
            room_goto(b[i].room);
        }

    }
}

void mainMouse(int button, int pressed, int x, int y)
{
    realMainMouse(button, !pressed, x, room_height - y);
}

void mainPassive(int x, int y)
{
    y = room_height - y;
    for (int i = 0; i < buttonsNo; i++)
    {
        b[i].over = 0;
        if (b[i].inside(x, y))
        {
            b[i].over = 1;
        }
    }
    glutPostRedisplay();
}

void mainKeyboard(unsigned char button, int x, int y)
{
    button = tolower(button);
    glutPostRedisplay();
}

void mainSpecial(int key, int x, int y)
{
    glutPostRedisplay();
}

