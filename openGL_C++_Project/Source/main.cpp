#include "myLibrary.h"
using namespace std;

void room_goto()
{
    roomPointer(mainMenu, mainMouse, mainKeyboard, mainSpecial, mainPassive, "Main Menu");
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(room_width,room_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("");
    room_goto();
    myInit();
    glutMainLoop();
    return 0;
}




