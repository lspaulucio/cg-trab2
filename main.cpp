#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <iostream>
#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "sources/janela.h"
#include "sources/retangulo.h"
#include "sources/circulo.h"

using namespace tinyxml2;
using namespace std;

int main(int argc, char** argv)
{
    const char config_file_name[] = "config.xml";
    char *path = argv[1];

    string svg_name, svg_type, svg_path;
    XMLDocument config_file, svg_file;
    XMLElement *pElem;
    XMLNode *pRoot;

    if(!path) //Verify if the path was provided
    {
        cout << "Path to config file not provided, the program will be finished" << endl;
        exit(1);
    }

    string pathFile = path;
    pathFile += config_file_name;
    //cout << pathFile << endl;

    //Opening file
    XMLError statusLoad = config_file.LoadFile(pathFile.c_str());

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

    cout << pathFile << endl;

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
    vector<Circulo*> circulos;
    pElem = pRoot->FirstChildElement();
    cout << pElem->Value() << endl;

    for(; pElem != NULL; pElem = pElem->NextSiblingElement())
    {
        string tipo = pElem->Value();

        if(!tipo.compare("circle"))
        {
            Circulo *c = new Circulo();
            c->setId(pElem->FindAttribute("id")->Value());
            cout << pElem->FindAttribute("cx")->Value() << endl;
            cout << pElem->FindAttribute("id")->Value() << endl;
            circulos.push_back(c);
        }
    }

    for(vector<Circulo*>::iterator it = circulos.begin(); it != circulos.end(); it++)
        cout << (*it)->getId() << endl;

    
    return EXIT_SUCCESS;
}