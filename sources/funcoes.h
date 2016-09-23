#ifndef FUNCOES_H
#define FUNCOES_H

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <vector>
#include "types.h"
#include "../tinyxml2/tinyxml2.h"
#include "janela.h"
#include "circulo.h"
#include "retangulo.h"

using namespace std;
using namespace tinyxml2;

void readXMLFile(const char*, Retangulo&, vector<Circulo>&);

//OpenGL functions

void init(void);
void display(void);
void idle(void);
void mouse(int, int, int, int);
void mouseMotion(int, int);

#endif //FUNCOES_H
