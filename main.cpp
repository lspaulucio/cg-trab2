#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <iostream>
#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "sources/funcoes.h"
#include "sources/janela.h"
#include "sources/retangulo.h"
#include "sources/circulo.h"

using namespace tinyxml2;
using namespace std;

//Global variables
Janela MainWindow;
vector<Circulo> circulos;
Retangulo rect;

int main(int argc, char** argv)
{
    readXMLFile(argv[1], rect, circulos);

    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // glutInitWindowSize(MainWindow.getWidth(),MainWindow.getHeight());
    // glutInitWindowPosition(100,100);
    // glutCreateWindow(MainWindow.getTitle().c_str());
    // init();
    // glutDisplayFunc(display);
    // glutMouseFunc(mouse);
    // glutMotionFunc(mouseMotion);
    // glutIdleFunc(idle);
    // glutMainLoop();


    return EXIT_SUCCESS;
}
