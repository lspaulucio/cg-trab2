#include "circulo.h"

Circulo::Circulo()
{
    radius = 0;
    xc = yc = 0;
}

float Circulo::getRadius() const
{
    return this->radius;
}

void Circulo::setRadius(float radius)
{
    this->radius = radius;
}

const float* Circulo::getRGBColors() const
{
    return RGBColors;
}

const float Circulo::getRGBColors(COLOR_ID id) const
{
    return RGBColors[id];
}

void Circulo::setRGBColors(const float colors[3])
{
    for(int i = 0; i < 3; i++)
        this->RGBColors[i] = colors[i];
}

float Circulo::getXc() const
{
    return xc;
}

void Circulo::setXc(float xc)
{
    this->xc = xc;
}

float Circulo::getYc() const
{
    return yc;
}

void Circulo::setYc(float yc)
{
    this->yc = yc;
}

const std::string &Circulo::getId() const
{
    return id;
}

void Circulo::setId(const std::string &id)
{
    this->id = id;
};

void Circulo::translate(float dx, float dy)
{
    this->xc += dx;
    this->yc += dy;
}

bool Circulo::insideCircle(float x, float y) const
{
    float dx, dy, dist;

    dx = this->xc - x;
    dy = this->yc - y;

    dist = sqrt((dx*dx) + (dy*dy));

    if(dist <= radius) {
        return true;
    }
    else {
        return false;
    }
}

Circulo::~Circulo(){}

