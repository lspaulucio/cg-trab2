#include "funcoes.h"

void readXMLFile(const char *path, Janela& MainWindow, Quadrado& Square)
{
    const char config_file_name[] = "config.xml";

    XMLDocument xml_file;
    XMLElement *pElem;
    XMLNode *pRoot;
    int width, height;
    int length;
    float colors[3];

    if(!path) //Verify if the path was provided
    {
        cout << "Path to config file not provided, the program will be finished" << endl;
        exit(1);
    }

    string pathFile = path;
    pathFile += config_file_name;
    //cout << pathFile << endl;

    //Opening file
    XMLError statusLoad = xml_file.LoadFile(pathFile.c_str());

    if(statusLoad != XML_SUCCESS) //Test if file has been opened correctly
    {
        cerr << "Error opening file" << endl;
        exit(XML_ERROR_FILE_READ_ERROR);
    }

    pRoot = xml_file.FirstChild(); //Get first element

    if(!pRoot)
    {
        cerr << "Error parsing element\n Program will be terminated" << endl;
        exit(XML_ERROR_PARSING_ELEMENT);
    }

    //cout << pRoot->Value() << endl;

    //arquivo da arena
    pElem->FirstChildElement("arquivoDaArena").;
    pElem->FirstChildElement("fundo")->QueryAttribute("corG", &colors[GREEN]);
    pElem->FirstChildElement("fundo")->QueryAttribute("corB", &colors[BLUE]);
    //cout << "CorR " << colors[RED] << " CorG " << colors[GREEN] << " CorB " << colors[BLUE] << endl;
    return;
}

//OpenGL functions

extern bool ALTERATION_STATE, INSIDE_SQUARE, DRAWN_FLAG;
extern float mx_click, my_click;
extern Janela MainWindow;
extern Quadrado Square;

void init(void)
{
    /*Selecting background color*/
    //cout << " Janela "<< MainWindow.getBgColors(RED) << MainWindow.getBgColors(GREEN) << MainWindow.getBgColors(BLUE) << endl;
    glClearColor(MainWindow.getBgColors(RED),MainWindow.getBgColors(GREEN),MainWindow.getBgColors(BLUE), 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,MainWindow.getWidth(),0.0,MainWindow.getHeight(),-1.0,1.0);
}

void display(void)
{
    /*Cleaning pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    if(DRAWN_FLAG)
    {
        glColor3fv((GLfloat*)(Square.getRGBColors()));
        glBegin(GL_POLYGON);
        for(int i = 0; i < 4; i++)
            glVertex3fv((GLfloat*)(Square.getVertices(i)));
        glEnd();
//        cout << Square.getVertices(3)[0] << endl;
    }
    glutSwapBuffers();
}

void idle(void)
{
    glutPostRedisplay();
}

void mouse(int key, int state, int x, int y)
{
    int hy = MainWindow.getHeight();
    bool inside;

    y = hy - y; //Adjusting Y-Axis

    inside = Square.insideSquare(x,y); //Test if the mouse click was inside of the square

    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && DRAWN_FLAG == false)
    {
        DRAWN_FLAG = true;
        Square.setXc(x);
        Square.setYc(y);
        Square.updateVertices();
        ALTERATION_STATE = true;

    } else if(inside && key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            mx_click = x;
            my_click = y;
            INSIDE_SQUARE = true;
        }
        else INSIDE_SQUARE = false;

    if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if(inside)
        {
            DRAWN_FLAG = false;
            ALTERATION_STATE = false;
        }
    }
}

void mouseMotion(int x, int y)
{
    if(ALTERATION_STATE && INSIDE_SQUARE)
    {
        int hy = MainWindow.getHeight();
        float dx, dy;

        y = hy - y; //Adjusting Y-Axis

        //calculating difference between mouse position and square's center
        dx = x - mx_click;
        dy = y - my_click;

        Square.translate(dx, dy);

        //Updating mouse position
        mx_click = x;
        my_click = y;
    }
}