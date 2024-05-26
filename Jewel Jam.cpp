#include <GL/glut.h>
#include "GameBoard.h"

GameBoard board;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    board.drawBoard();
    glutSwapBuffers();
}

void initGL() {
    glClearColor(0.9569, 0.9176, 0.8784, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1280.0, 0.0, 720.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouseClick(int button, int state, int x, int y) {
    board.handleMouseClick(button, state, x, y);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Match-3 Game");
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    initGL();
    glutMainLoop();
    return 0;
}
