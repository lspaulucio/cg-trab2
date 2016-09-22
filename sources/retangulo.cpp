#include "retangulo.h"

Retangulo::Retangulo()
{
   width = height = 0;
    xc = yc = 0;
    for(int i = 0; i < 3; i++)
        vertices[i][Z_AXIS] = 0;
}

void Retangulo::setHeight(float height) {
   this->height = height;
}

const float* Retangulo::getRGBColors() const
{
    return RGBColors;
}

const float Retangulo::getRGBColors(COLOR_ID id) const
{
    return RGBColors[id];
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
