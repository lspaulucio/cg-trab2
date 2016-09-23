#include "retangulo.h"

Retangulo::Retangulo()
{
   width = height = 0;
    xc = yc = 0;
    for(int i = 0; i < 3; i++)
        vertices[i][Z_AXIS] = 0;
}

float Retangulo::getHeight() const
{
   return height;
}

void Retangulo::setHeight(float height)
{
    this->height = height;
}

float Retangulo::getWidth() const
{
   return width;
}

void Retangulo::setWidth(float width)
{
   this->width = width;
}

const float* Retangulo::getRGBColors() const
{
    return RGBColors;
}

const float Retangulo::getRGBColors(COLOR_ID id) const
{
    return RGBColors[id];
}

int Retangulo::colorVerification(std::string color) //Check the color's name
{
    if(!color.compare("white")) //If color is white
        return WHITE;
    if(!color.compare("black")) //If color is black
        return BLACK;
    if(!color.compare("red")) //If color is red
        return RED;
    if(!color.compare("green")) //If color is green
        return GREEN;
    if(!color.compare("blue")) //If color is blue
        return BLUE;

    return -1;
}

void Retangulo::setRGBColors(std::string color_name)
{
    float colors[3] = {0.0};

    switch(colorVerification(color_name)) //Choose RGB values for each color's type
    {
        case BLACK:
            this->setRGBColors(colors);
            break;
        case WHITE:
            colors[RED]= colors[GREEN] = colors[BLUE] = 1.0;
            this->setRGBColors(colors);
            break;
        case RED:
            colors[RED] = 1.0;
            this->setRGBColors(colors);
            break;
        case GREEN:
            colors[GREEN] = 1.0;
            this->setRGBColors(colors);
            break;
        case BLUE:
            colors[BLUE] = 1.0;
            this->setRGBColors(colors);
            break;
        default:
            std::cout << "Unknown color" << std::endl;
    }
}

void Retangulo::setRGBColors(const float colors[3])
{
    for(int i = 0; i < 3; i++)
        Retangulo::RGBColors[i] = colors[i];
}

float Retangulo::getXc() const
{
    return xc;
}

void Retangulo::setXc(float xc)
{
    this->xc = xc;
}

float Retangulo::getYc() const
{
    return yc;
}

void Retangulo::setYc(float yc)
{
    this->yc = yc;
}

const std::string &Retangulo::getId() const
{
    return id;
}

void Retangulo::setId(const std::string &id)
{
    this->id = id;
};

const float* Retangulo::getVertices(int n) const
{
    return vertices[n];
}

const float Retangulo::getVertices(int n, AXES a) const
{
    return vertices[n][a];
}

void Retangulo::translate(float dx, float dy)
{
    this->xc += dx;
    this->yc += dy;
    updateVertices();
}

void Retangulo::updateVertices()
{
    //counter clock-wise
    //Vertice one already in correct position

//    vertices[0][X_AXIS] = this->xc;
//    vertices[0][Y_AXIS] = this->yc;

    //Vertice two
    vertices[1][X_AXIS] = this->xc;
    vertices[1][Y_AXIS] = this->yc - height;
    //Vertice three
    vertices[2][X_AXIS] = this->xc + width;
    vertices[2][Y_AXIS] = this->yc - height;
    //Vertice four
    vertices[3][X_AXIS] = this->xc + width;
    vertices[3][Y_AXIS] = this->yc;
}

bool Retangulo::insideSquare(float x, float y) const
{
    if(x >= vertices[0][X_AXIS] && x <= vertices[3][X_AXIS] && y <= vertices[0][Y_AXIS] && y >= vertices[1][Y_AXIS])
        return true;
    else
        return false;
}

Retangulo::~Retangulo(){}
