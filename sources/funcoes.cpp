#include "funcoes.h"

void readXMLFile(const char *path, Retangulo &rect, vector<Circulo> &circulos)
{
    const char config_file_name[] = "config.xml";

    string svg_name, svg_type, svg_path, pathFile;
    XMLDocument config_file, svg_file;
    XMLError statusLoad;
    XMLElement *pElem;
    XMLNode *pRoot;

    if(!path) //Verify if the path was provided
    {
        cout << "Path to config file not provided, the program will be finished" << endl;
        exit(1);
    }

    pathFile = path;
    pathFile += config_file_name;
    //cout << pathFile << endl;

    //Opening file
    statusLoad = config_file.LoadFile(pathFile.c_str());

    if(statusLoad != XML_SUCCESS) //Test if file has been opened correctly
    {
        cerr << "Error opening file" << endl;
        exit(XML_ERROR_FILE_READ_ERROR);
    }

    pRoot = config_file.FirstChild(); //Get first element

    if(!pRoot)
    {
        cerr << "Error parsing element\n Program will be terminated" << endl;
        exit(XML_ERROR_PARSING_ELEMENT);
    }
    //cout << pRoot->Value() << endl;

    //config.xml file
    pElem = pRoot->FirstChildElement("arquivoDaArena");
    svg_name = pElem->FindAttribute("nome")->Value();
    svg_type = pElem->FindAttribute("tipo")->Value();
    svg_path = pElem->FindAttribute("caminho")->Value();

//    cout << name << endl;
//    cout << type << endl;
//    cout << svg_path << endl;

    //Path and name to svg file
    pathFile = svg_path;
    pathFile += svg_name += ".";
    pathFile += svg_type;

    //cout << pathFile << endl;

    //SVG file
    statusLoad = svg_file.LoadFile(pathFile.c_str());

    if(statusLoad != XML_SUCCESS) //Test if file has been opened correctly
    {
        cerr << "Error opening file" << endl;
        exit(XML_ERROR_FILE_READ_ERROR);
    }

    pRoot = svg_file.FirstChild(); //Get first element

    if(!pRoot)
    {
        cerr << "Error parsing element\n Program will be terminated" << endl;
        exit(XML_ERROR_PARSING_ELEMENT);
    }
//    cout << pRoot->Value() << endl;

    pElem = pRoot->FirstChildElement();
    // cout << pElem->Value() << endl;

    for(; pElem != NULL; pElem = pElem->NextSiblingElement())
    {
        string tipo = pElem->Value();

        if(!tipo.compare("circle")) //If is a circle
        {
            Circulo c;
            c.setXc(atof(pElem->FindAttribute("cx")->Value()));
            c.setYc(atof(pElem->FindAttribute("cy")->Value()));
            c.setRadius(atof(pElem->FindAttribute("r")->Value()));
            c.setId(pElem->FindAttribute("id")->Value());
            c.setRGBColors(pElem->FindAttribute("fill")->Value());

            // cout << pElem->FindAttribute("cx")->Value() << endl;
            // cout << pElem->FindAttribute("cy")->Value() << endl;
            // cout << pElem->FindAttribute("r")->Value() << endl;
            // cout << pElem->FindAttribute("id")->Value() << endl;
            // cout << pElem->FindAttribute("fill")->Value() << endl;

            //cout << "Circulo " << "cx: " << c.getXc() << " cy: " << c.getYc() << " r: " << c.getRadius() <<
            //" colors: " << c.getRGBColors(RED) << ", " << c.getRGBColors(GREEN) << ", " << c.getRGBColors(BLUE) << endl;
            circulos.push_back(c);
        }
        else if(!tipo.compare("rect")) //If is a rectangle
            {
                rect.setXc(atof(pElem->FindAttribute("x")->Value()));
                rect.setYc(atof(pElem->FindAttribute("y")->Value()));
                rect.setWidth(atof(pElem->FindAttribute("width")->Value()));
                rect.setHeight(atof(pElem->FindAttribute("height")->Value()));
                rect.setId(pElem->FindAttribute("id")->Value());
                rect.setRGBColors(pElem->FindAttribute("fill")->Value());

                // cout << pElem->FindAttribute("cx")->Value() << endl;
                // cout << pElem->FindAttribute("cy")->Value() << endl;
                // cout << pElem->FindAttribute("r")->Value() << endl;
                // cout << pElem->FindAttribute("id")->Value() << endl;
                // cout << pElem->FindAttribute("fill")->Value() << endl;

                //cout << "Retangulo " << "x: " << rect.getXc() << " y: " << rect.getYc() <<
                //" width: " << rect.getWidth() << " height: " << rect.getHeight() << " colors: " <<
                //rect.getRGBColors(RED) << ", " << rect.getRGBColors(GREEN) << ", " << rect.getRGBColors(BLUE) << endl;
            }
    }

    for(vector<Circulo>::iterator it = circulos.begin(); it != circulos.end(); it++)
        cout << (*it).getId() << endl;

    return;
}

//OpenGL functions


// extern bool ALTERATION_STATE, INSIDE_SQUARE, DRAWN_FLAG;
// extern float mx_click, my_click;
// extern Janela MainWindow;
// extern Quadrado Square;
//
// void init(void)
// {
//     /*Selecting background color*/
//     //cout << " Janela "<< MainWindow.getBgColors(RED) << MainWindow.getBgColors(GREEN) << MainWindow.getBgColors(BLUE) << endl;
//     glClearColor(MainWindow.getBgColors(RED),MainWindow.getBgColors(GREEN),MainWindow.getBgColors(BLUE), 0.0);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(0.0,MainWindow.getWidth(),0.0,MainWindow.getHeight(),-1.0,1.0);
// }
//
// void display(void)
// {
//     /*Cleaning pixels */
//     glClear(GL_COLOR_BUFFER_BIT);
//
//     if(DRAWN_FLAG)
//     {
//         glColor3fv((GLfloat*)(Square.getRGBColors()));
//         glBegin(GL_POLYGON);
//         for(int i = 0; i < 4; i++)
//             glVertex3fv((GLfloat*)(Square.getVertices(i)));
//         glEnd();
// //        cout << Square.getVertices(3)[0] << endl;
//     }
//     glutSwapBuffers();
// }
//
// void idle(void)
// {
//     glutPostRedisplay();
// }
//
// void mouse(int key, int state, int x, int y)
// {
//     int hy = MainWindow.getHeight();
//     bool inside;
//
//     y = hy - y; //Adjusting Y-Axis
//
//     inside = Square.insideSquare(x,y); //Test if the mouse click was inside of the square
//
//     if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN && DRAWN_FLAG == false)
//     {
//         DRAWN_FLAG = true;
//         Square.setXc(x);
//         Square.setYc(y);
//         Square.updateVertices();
//         ALTERATION_STATE = true;
//
//     } else if(inside && key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//         {
//             mx_click = x;
//             my_click = y;
//             INSIDE_SQUARE = true;
//         }
//         else INSIDE_SQUARE = false;
//
//     if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//     {
//         if(inside)
//         {
//             DRAWN_FLAG = false;
//             ALTERATION_STATE = false;
//         }
//     }
// }
//
// void mouseMotion(int x, int y)
// {
//     if(ALTERATION_STATE && INSIDE_SQUARE)
//     {
//         int hy = MainWindow.getHeight();
//         float dx, dy;
//
//         y = hy - y; //Adjusting Y-Axis
//
//         //calculating difference between mouse position and square's center
//         dx = x - mx_click;
//         dy = y - my_click;
//
//         Square.translate(dx, dy);
//
//         //Updating mouse position
//         mx_click = x;
//         my_click = y;
//     }
// }
