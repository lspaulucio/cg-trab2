#include "funcoes.h"

extern Janela MainWindow;
extern Circulo player;
extern Circulo arena[2];
extern Retangulo rect;
extern vector<Circulo> enemies;
extern int key_status[256];

void readXMLFile(const char *path)
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
            if(!c.getId().compare("Jogador"))
                player = c;
            else if(!c.getId().compare("Pista"))
                {
                    if(arena[0].getRadius() > c.getRadius())
                        arena[1] = c;
                    else{
                            arena[1] = arena[0];
                            arena[0] = c;
                        }
                }
                else enemies.push_back(c);
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

                // cout << "Retangulo " << "x: " << rect.getXc() << " y: " << rect.getYc() <<
                // " width: " << rect.getWidth() << " height: " << rect.getHeight() << " colors: " <<
                // rect.getRGBColors(RED) << ", " << rect.getRGBColors(GREEN) << ", " << rect.getRGBColors(BLUE) << endl;
            }
    }//End of file read

    MainWindow.setHeight(2*arena[0].getRadius());
    MainWindow.setWidth(2*arena[0].getRadius());
    MainWindow.setTitle("Arena");

    //Adjusting Y-Axis -> y = hy - y;
    for(int i = 0; i < 2; i++)
        arena[i].setYc(MainWindow.getHeight() - arena[i].getYc());

    rect.setYc(MainWindow.getHeight() - rect.getYc());
    rect.updateVertices();
    // cout << "x: " << rect.getXc() << "y: " << rect.getYc() << endl;

    for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
        (*it).setYc(MainWindow.getHeight() - (*it).getYc());

    player.setYc(MainWindow.getHeight() - player.getYc());

    // for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
    //     cout << (*it).getId() << endl;

    return;
}

//OpenGL functions

void drawRectangle(Retangulo &rect)
{
    glColor3fv((GLfloat*)(rect.getRGBColors()));
    glBegin(GL_POLYGON);
        for(int i = 0; i < 4; i++)
            glVertex3fv((GLfloat*)(rect.getVertices(i)));
    glEnd();
}

void drawCircle(Circulo &circ)
{
    float dx, dy;
    glColor3fv((GLfloat*)(circ.getRGBColors()));
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(circ.getXc(), circ.getYc());
		for(int i = 0; i <= circ.getDrawResolution(); i++)
        {
            dx = circ.getXc() + (circ.getRadius() * cos(i * 2.0*M_PI / circ.getDrawResolution()));
            dy = circ.getYc() + (circ.getRadius() * sin(i * 2.0*M_PI / circ.getDrawResolution()));
			glVertex2f(dx, dy);
		}
    glEnd();
}

void init(void)
{
    GLfloat xi, xf;
    GLfloat yi, yf;

    /*Selecting background color*/
    //cout << " Janela "<< MainWindow.getBgColors(RED) << MainWindow.getBgColors(GREEN) << MainWindow.getBgColors(BLUE) << endl;
    glClearColor(MainWindow.getBgColors(RED),MainWindow.getBgColors(GREEN),MainWindow.getBgColors(BLUE), 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    xi = arena[0].getXc() - arena[0].getRadius();
    xf = arena[0].getXc() + arena[0].getRadius();
    yi = arena[0].getYc() - arena[0].getRadius();
    yf = arena[0].getYc() + arena[0].getRadius();

    glOrtho(xi,xf,yi,yf,-1.0,1.0);
}

void display(void)
{
    /*Cleaning pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i=0; i < 2; i++)
        drawCircle(arena[i]);

    drawRectangle(rect);

    for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
        drawCircle(*it);

    drawCircle(player);

    glutSwapBuffers();
}

void idle(void)
{
    float dx = 0, dy = 0;
    float tx, ty;
    const int STEP = 3;

    if(key_status['w'])
        dy += STEP;
    if(key_status['s'])
        dy -= STEP;
    if(key_status['d'])
        dx += STEP;
    if(key_status['a'])
        dx -= STEP;

    tx = player.getXc();
    ty = player.getYc();

    player.setXc(tx + dx);
    player.setYc(ty + dy);
    bool teste = true;

    for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        teste = teste && (*it).outsideCircle(player);
    }

    if(arena[0].insideCircle(player) && arena[1].outsideCircle(player) && teste);
    else
    {
        player.setXc(tx);
        player.setYc(ty);
    }

    glutPostRedisplay();
}

void keyUp (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
          key_status['w'] = 0;
          break;

        case 's':
        case 'S':
          key_status['s'] = 0;
          break;

        case 'd':
        case 'D':
          key_status['d'] = 0;
          break;

        case 'a':
        case 'A':
          key_status['a'] = 0;
          break;
      }
}

void keypress (unsigned char key, int x, int y)
{
  switch (key)
  {
      case 'w':
      case 'W':
        //gy += 0.1;
        key_status['w'] = 1;
        break;

      case 's':
      case 'S':
        // gy -= 0.1;
        key_status['s'] = 1;
        break;

      case 'd':
      case 'D':
        // gx += 0.1;
        key_status['d'] = 1;
        break;

      case 'a':
      case 'A':
        // gx -= 0.1;
        key_status['a'] = 1;
        break;

      case 'e':
        exit(0);
  }
}
